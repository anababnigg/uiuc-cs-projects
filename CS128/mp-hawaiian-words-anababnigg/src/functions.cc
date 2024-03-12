#include "functions.hpp"

#include <iostream>
#include <string>
#include <vector>

/**
 * TODO: Implement this function
 * @param word word to change to lowercase
 * @return result of changing every character in word to lowercase
 */
std::string StringToLower(const std::string& word) {
  // std::cout << "Input to StringToLower() : " << word << std::endl;
  // return word;
  std::string lowercase;
  for (unsigned int i = 0; i < word.length(); i++) {
    lowercase += (char)tolower(word.at(i));
  }
  return lowercase;
}

/**
 * TODO: Implement this function
 * @param v1 first character in potential vowel group
 * @param v2 second character in potential vowel group
 * @return true if v1 and v2 form a valid vowel group
 */
bool IsVowelGroup(const char& v1, const char& v2) {
  // std::cout << "Input to IsVowelGroup() : \"" << v1 << "\" \"" << v2 << "\""
  // << std::endl; return true;
  bool isvc = false;
  const std::vector<char> kAfterA = {'e', 'i', 'o', 'u'};
  if (v1 == 'a') {
    isvc = std::find(kAfterA.begin(), kAfterA.end(), v2) != kAfterA.end();
  }
  if (v1 == 'e') {
    isvc = (v2 == 'i' || v2 == 'u');
  }
  if (v1 == 'i' && v2 == 'u') {
    isvc = true;
  }
  if (v1 == 'o' && (v2 == 'i' || v2 == 'u')) {
    isvc = true;
  }
  if (v1 == 'u' && v2 == 'i') {
    isvc = true;
  }
  return isvc;
}

/**
 * TODO: Complete this function
 * @param v potential vowel character
 * @return true if v is a vowel
 */
bool IsVowel(const char& v) {
  // std::cout << "Input to IsVowel() : \"" << v << "\"" << std::endl;
  // return true;
  const std::vector<char> kVowels = {'a', 'e', 'i', 'o', 'u'};
  return (std::find(kVowels.begin(), kVowels.end(), v) != kVowels.end());
}

/**
 * TODO: Complete this function
 * @param c potential consonant character
 * @return true if c is a consonant
 */
bool IsConsonant(const char& c) {
  // std::cout << "Input to IsConsonant() : \"" << c << "\"" << std::endl;
  // return true;
  const std::vector<char> kConsonants = {'p', 'k', 'h', 'l', 'm', 'n', 'w'};
  return (std::find(kConsonants.begin(), kConsonants.end(), c) !=
          kConsonants.end());
}

/**
 * TODO: Implement this function
 * @param c character to check validity of
 * @return true if input c is a valid character in the Hawaiian language, false
 * otherwise
 */
bool IsValidCharacter(const char& c) {
  // std::cout << "Input to IsValidCharacter() : \"" << c << "\"" << std::endl;
  // return true;
  const std::vector<char> kValids = {
      'a', 'e', 'i', 'o', 'u', 'p', 'k', 'h', 'l', 'm', 'n', 'w', ' ', '\''};
  return (std::find(kValids.begin(), kValids.end(), c) != kValids.end());
}

/**
 * TODO: Implement this function
 * @param word word to check validity of
 * @return true if every character in word is a valid character in the Hawaiian
 * language, false otherwise
 */
bool IsValidWord(const std::string& word) {
  // std::cout << "Input to IsValidWord() : " << word << std::endl;
  // return true;
  for (size_t i = 0; i < word.length(); i++) {
    const std::vector<char> kValids = {
        'a', 'e', 'i', 'o', 'u', 'p', 'k', 'h', 'l', 'm', 'n', 'w', ' ', '\''};
    if (std::find(kValids.begin(), kValids.end(), word.at(i)) ==
        kValids.end()) {
      return false;
    }
  }
  return true;
}

/**
 * TODO: Implement this function
 * @param c consonant to get pronunciation of
 * @param prev character before c, used for determining w translation
 *    set to null character as default if no value is passed in
 * @return pronunciation of the consonant c as a char
 */
char ConsonantPronunciation(const char& c, const char& prev) {
  // std::cout << "Input to ConsonantPronunciation() : \"" << c << "\" \"" <<
  // prev << "\"" << std::endl; return '\0'; const std::vector<char> kConsonants
  // = {'p', 'k', 'h', 'l', 'm', 'n'}; if the constant isn't w...
  char rchar = '\0';
  if (c == 'w' && (prev == 'i' || prev == 'e')) {
    rchar = 'v';
  }
  if (c == 'w' && prev != 'i' && prev != 'e') {
    rchar = 'w';
  } else {
    rchar = c;
  }
  return rchar;
}

/**
 * TODO: Implement this function
 * @param v1 first vowel in a vowel grouping
 * @param v2 second vowel in a vowel grouping
 * @return the pronunciation of the vowel grouping made up of v1 and v2
 * as a string
 */
std::string VowelGroupPronunciation(const char& v1, const char& v2) {
  // std::cout << "Input to VowelGroupPronunciation() : \"" << v1 << "\" \"" <<
  // v2 << "\"" << std::endl; return ""; for A:
  if (v1 == 'a') {
    if (v2 == 'e' || v2 == 'i') {
      return "eye";
    }
    if (v2 == 'o' || v2 == 'u') {
      return "ow";
    }
  }
  // for E:
  if (v1 == 'e') {
    if (v2 == 'i') {
      return "ay";
    }
    if (v2 == 'u') {
      return "eh-oo";
    }
  }
  // for I:
  if (v1 == 'i' && v2 == 'u') {
    return "ew";
  }
  // for O:
  if (v1 == 'o') {
    if (v2 == 'i') {
      return "oy";
    }
    if (v2 == 'u') {
      return "ow";
    }
  }
  // for U:
  if (v1 == 'u' && v2 == 'i') {
    return "ooey";
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param v single vowel to get pronunciation of
 * @return the pronunciation of v as a string
 */
std::string SingleVowelPronunciation(const char& v) {
  // std::cout << "Input to SingleVowelPronunciation() : \"" << v << "\"" <<
  // std::endl; return "";
  if (v == 'a') {
    return "ah";
  }
  if (v == 'e') {
    return "eh";
  }
  if (v == 'i') {
    return "ee";
  }
  if (v == 'o') {
    return "oh";
  }
  if (v == 'u') {
    return "oo";
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param prev first character in set of three passed to function
 * @param curr second character in set of three passed to function
 * @param next third character in set of three passed to function
 * @return pronunciation of curr using next and prev as needed to determine
 * result
 */
std::string ProcessCharacter(const char& prev,
                             const char& curr,
                             const char& next) {
  // std::cout << "Input to ProcessCharacter() : \"" << prev << "\" \"" << curr
  // << "\" \"" << next << "\"" << std::endl; on each input, see if it runs
  std::string pp;
  // check first letter (they would be equal because that is the default)
  if (prev == curr) {
    if (IsVowelGroup(curr, next)) {
      pp = VowelGroupPronunciation(curr, next);
    } else if (IsVowel(curr)) {
      pp = SingleVowelPronunciation(curr);
    } else {
      pp = ConsonantPronunciation(curr);
    }
  }

  // check if last letter (also equal) (not a vowel group), but was it a vowel
  if (next == curr) {
    if (!IsVowelGroup(prev, curr)) {
      if (IsVowel(curr)) {
        pp = SingleVowelPronunciation(curr);
      }
    }
  }
  // check if its a normal intermediate value
  if (curr != prev && curr != next) {
    if (!IsVowelGroup(prev, curr)) {
      if (IsVowelGroup(curr, next)) {
        pp = VowelGroupPronunciation(curr, next);
      } else if (IsVowel(curr)) {
        pp = SingleVowelPronunciation(curr);
      } else {
        pp = ConsonantPronunciation(curr);
      }
    }
  }
  return pp;
}

/**
 * TODO: Implement this function
 * @param word string to get pronunciation of
 * @return pronunciation of word
 */
std::string Pronunciation(const std::string& word) {
  std::cout << "Input to Pronunciation() : " << word << std::endl;
  // main string to output
  std::string pronunced;
  for (unsigned int i = 0; i < word.length(); i++) {
    char curr = word.at(i);

    // check if dash
    std::string dash;

    if (i == 0) {
      char prev = word.at(i);
      char next = word.at(i + 1);
      if (!IsConsonant(curr) && next != ' ' && curr != ' ' &&
          !IsVowelGroup(prev, curr) && next != '\'' && curr != '\'' &&
          !IsVowelGroup(curr, next)) {
        dash = "-";
      }
      pronunced += ProcessCharacter(prev, curr, next) + dash;
    } else if (i == word.length() - 1) {
      char prev = word.at(i - 1);
      char next = word.at(i);
      pronunced += ProcessCharacter(prev, curr, next);
    } else if (i != 0 && i != word.length() - 1) {
      char prev = word.at(i - 1);
      char next = word.at(i + 1);
      if (!IsConsonant(curr) && next != ' ' && curr != ' ' &&
          !IsVowelGroup(prev, curr) && next != '\'' && curr != '\'' &&
          !IsVowelGroup(curr, next)) {
        dash = "-";
      }
      pronunced += ProcessCharacter(prev, curr, next) + dash;
    }
  }
  return pronunced;
}

/**
 * TODO: Implement this function
 * @param hawaiian_word word to get pronunciation of
 * @return the pronunciation of hawaiian_word as a string if valid
 *  and throws an invalid_argument error if not valid
 */
std::string GetPronunciation(const std::string& hawaiian_word) {
  std::cout << "Input to GetPronunciation() : " << hawaiian_word << std::endl;
  std::string word = StringToLower(hawaiian_word);
  if (!IsValidWord(word)) {
    throw std::invalid_argument("nuh uh");
  }
  return Pronunciation(word);
}