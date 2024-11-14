#include <iostream>
#include <string>
#include <unordered_map>

struct WordNode {
    std::string word;         //Từ vựng trong câu
    WordNode* next;           //Trỏ đến node kế

    WordNode(std::string w) : word(w), next(nullptr) {}
};

struct WordList {
    WordNode* head;

    WordList() : head(nullptr) {}

    //Thêm từ vào ds
    void addWord(std::string word) {
        WordNode* newNode = new WordNode(word);
        if (head == nullptr) {
            head = newNode;
        } else {
            WordNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    //Xđ từ xuất hiện nhiều nhất trong câu
    std::string findMostFrequentWord() {
        std::unordered_map<std::string, int> wordCount;
        WordNode* current = head;
        while (current != nullptr) {
            wordCount[current->word]++;
            current = current->next;
        }

        int maxCount = 0;
        std::string mostFrequentWord;
        for (const auto& pair : wordCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequentWord = pair.first;
            }
        }
        return mostFrequentWord;
    }

    //Loại từ lặp 
    void removeDuplicateWords() {
        WordNode* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->word == current->next->word) {
                WordNode* duplicate = current->next;
                current->next = duplicate->next;
                delete duplicate;
            } else {
                current = current->next;
            }
        }
    }

    //Đếm số từ trong câu (không trùng)
    int countUniqueWords() {
        std::unordered_map<std::string, bool> uniqueWords;
        WordNode* current = head;
        while (current != nullptr) {
            uniqueWords[current->word] = true;
            current = current->next;
        }
        return uniqueWords.size();
    }

    //Hiển thị ds từ
    void displayWords() const {
        WordNode* current = head;
        while (current != nullptr) {
            std::cout << current->word << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    WordList wordList;

    wordList.addWord("trời");
    wordList.addWord("xanh");
    wordList.addWord("xanh");
    wordList.addWord("mây");
    wordList.addWord("trăng");
    wordList.addWord("trắng");
    wordList.addWord("nắng");
    wordList.addWord("vàng");
    wordList.addWord("còn");
    wordList.addWord("tôi");
    wordList.addWord("là");
    wordList.addWord("yr");
    wordList.addWord("nè");

    //Hiển thị ds từ ban đầu
    std::cout << "Danh sách từ ban đầu:\n";
    wordList.displayWords();

    //Xđ từ xuất hiện nhiều nhất
    std::string mostFrequentWord = wordList.findMostFrequentWord();
    std::cout << "Từ xuất hiện nhiều nhất: " << mostFrequentWord << std::endl;

    //Loại từ láy
    wordList.removeDuplicateWords();
    std::cout << "Danh sách từ sau khi loại bỏ từ láy:\n";
    wordList.displayWords();

    //Đếm số từ 
    int uniqueWordCount = wordList.countUniqueWords();
    std::cout << "Số từ vựng xuất hiện trong câu: " << uniqueWordCount << std::endl;

    return 0;
}
