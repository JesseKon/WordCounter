/**
 * Small function to count occurrence of words in given string literal.
 * 
 * -------------------------
 * Usage example:
 * 
 * auto result = WordCounter(words);
 * for (decltype(result)::const_iterator it = result.begin(); it != result.end(); ++it)
 *     std::wcout << it->first << '\t' << it->second << '\n';
 * 
 * -------------------------
 * To have words counted in reversed order:
 * 
 * auto result = WordCounter<int, std::wstring, std::less<int>>(words);
 */

#ifndef _WORD_COUNTER_H_
#define _WORD_COUNTER_H_

#include <string>
#include <map>
#include <typeinfo>

template <typename T = std::int32_t, typename S = std::wstring, typename K = std::greater<T>>
auto WordCounter(
    const S& input
) -> std::multimap<T, S, K> {
    typedef std::conditional<std::is_same<S, std::wstring>::value, wchar_t, char>::type char_type;
    S word;
    std::map<S, T> words;

    for (std::size_t i = 0; i < input.length(); ++i) {
        char_type c = static_cast<char_type>(std::tolower(input.at(i)));

        if (!std::isspace(c) && !std::isdigit(c) && !std::ispunct(c) && i != input.length() - 1) {
            word.push_back(c);
            continue;
        }

        if (!word.empty()) {
            auto find = words.find(word);
            if (find != words.end())
                ++find->second;
            else
                words.emplace(std::make_pair(word, 1));
        }

        word.clear();
    }

    std::multimap<T, S, K> wordsInOrder;
    for (typename std::map<S, T>::iterator it = words.begin(); it != words.end(); ++it)
        wordsInOrder.insert(std::make_pair(it->second, it->first));

    return wordsInOrder;
}

#endif  // _WORD_COUNTER_H_