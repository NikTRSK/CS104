#include "hashMap.h"

hashMap::hashMap() {
  sizes = {11, 23, 41, 83, 163, 331, 641, 1283, 2579, 5147, 10243, 20483, 40961};
  size = sizes.front();  // initial table size
  sizes.pop_front();  // remove the size
  numItems = 0; // initialize the num of items
  data = new std::vector<std::pair<std::string, int> > (size);
}

hashMap::~hashMap() {
  delete data;
}

void hashMap::add(const std::string& word) {
  // check if balance factor is > 0.5 and resize if needed
  resize();

  // probe until either an item is updated or an empty spot is found
  for (int i = 0; i <= sqrt(size); i++) {
  // calculate the index of the word
  int index = calculateHash(hash(word), i);
  // insert item
  // if index available then insert
  if (data->at(index).first.empty()) {
    data->at(index) = std::pair<std::string, int>(word, 1);
    numItems++;
    return;
  }
  else if (data->at(index).first == word) {
    // if we are inserting the same word increase count
      int cnt = data->at(index).second;
      data->at(index) = std::pair<std::string, int>(word, cnt+1);
      return;
    }
  }
}

std::vector<int> hashMap::bitHash(const std::string& substr) {
  long long preHash = 0;
  // calculate the preHash using 128^7 * a1 + 128^6 * a2 + ... + 128 * a7 + a8
  for (unsigned int pos = 0; pos < substr.size(); pos++)
    preHash += (long long)( (int)(substr.at(pos))*pow(128, substr.size()-pos-1) );

  // compute the hash
  std::vector<int> hash = {0, 0, 0, 0};

  // [0] is the most significant digit, hence the reverse loop
  long long temp = preHash;
  for (int i = 3; i >= 0; i--) {
    hash.at(i) = (int)(temp % 40961);
    temp = temp / 40961;
  }
  
  return hash;
}

int hashMap::hash(const std::string& word) {
  int substrSize = word.size();
  int w_i = 10;  // start at the last four digits
  int w[14] = {0};  // holds the w values

  while (substrSize >= 0) {
    // holds the temp values from the bitHash function
    std::vector<int> temp;
    if (substrSize - 8 >= 0)
      temp = bitHash(word.substr(substrSize-8, 8));
    else
      temp = bitHash(word.substr(0, substrSize));
    // edge case when there is a 28 word
    if (w_i == 0) { // we know that we only have two characters so run this.
      std::vector<int> t2;
      t2.push_back(temp.at(2)); t2.push_back(temp.at(3));
      temp = t2;
    }
    // copy over the temp array to the actual w values for use with the function
    for (unsigned int i = 0; i < temp.size(); i++)
      w[w_i + i] = temp.at(i);

    // resize the starting position for the next 8 letter word
    substrSize -= 8;
    // condition for the last chunk of a 28 letter word. 3*8 (4bit chunks) + 4 (2 bit chunk)
    if (w_i - 4 < 0)
      w_i -= 2;
    else
      w_i -= 4;
  }

  // array that holds all the multiples for a the hashing function
  int multBy[14] = {34394, 36706, 38074, 16351, 2623, 10174, 22339, 27779, 36642, 19250, 36216, 33514, 24019, 5552};
  
  // implements the calculation of the hashing equation by multiplying the two arrays
  long long hashValue = 0;
  for (int i = 0; i < 14; i++)
    hashValue += (long long)w[i] * multBy[i];

  return hashValue % size;
}

void hashMap::reportAll(std::ostream& output) {
  for (unsigned int i = 0; i < data->size(); i++) {
    if (!data->at(i).first.empty())
      output << data->at(i).first << " " << data->at(i).second << "\n";
  }
  output << numItems << std::endl;
}

void hashMap::resize() {
  if (numItems / (double)size >= 0.5) {
    if (sizes.empty())
      throw std::out_of_range("Hash table size limit reached.");
    size = sizes.front();
    sizes.pop_front();

    // create a new temp array with the values for the old vector
    std::vector<std::pair<std::string, int> > temp = *data;

    // resize the data array
    delete data;
    data = new std::vector<std::pair<std::string, int> > (size);

    // copy all the data elements
    for (unsigned int i = 0; i < temp.size(); i++) {
      if (!temp.at(i).first.empty()) {
        int cnt = temp.at(i).second;
        add(temp.at(i).first);
        data->at(i).second = cnt;
      }
    }
  }
}

int hashMap::calculateHash(int prevHash, int i) {
  return (prevHash + (int)pow(i,2)) % size;
}