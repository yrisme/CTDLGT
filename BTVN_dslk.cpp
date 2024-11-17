#include <iostream>
#include <string>

struct FileNode {
    std::string fileName;  //Tên file
    int size;              //Dung lượng file (MB)
    std::string timestamp; //Tgian lưu file
    FileNode* next;        //Trỏ đến file kế 

    FileNode(std::string name, int fileSize, std::string time) 
        : fileName(name), size(fileSize), timestamp(time), next(nullptr) {}
};

struct FileList {
    FileNode* head;

    FileList() : head(nullptr) {}

    //Thêm file vào ds theo thứ tự tăng dung lượng
    void addFileSorted(std::string name, int size, std::string time) {
        FileNode* newNode = new FileNode(name, size, time);
        if (!head || head->size > size) { //Chèn ở đầu nếu ds k có gì hoặc dung lượng min
            newNode->next = head;
            head = newNode;
            return;
        }

        FileNode* current = head;
        while (current->next && current->next->size <= size) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    //Xóa file đầu ds
    void deleteFromHead() {
        if (!head) return;
        FileNode* temp = head;
        head = head->next;
        delete temp;
    }

    //Xóa file cuối ds
    void deleteFromTail() {
        if (!head) return;

        if (!head->next) { //HĐ nếu chỉ có 1 node
            delete head;
            head = nullptr;
            return;
        }

        FileNode* current = head;
        while (current->next->next) { //Tìm node cận cuối
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
    }

    //Xóa file sau 1 node đã cho 
    void deleteAfterNode(FileNode* prevNode) {
        if (!prevNode || !prevNode->next) return;

        FileNode* temp = prevNode->next;
        prevNode->next = temp->next;
        delete temp;
    }

    //Xóa file có dung lượng min và tgian lưu lâu nhất
    void deleteSmallestAndOldest() {
        if (!head) return;

        FileNode* smallest = head; //File min nằm ở đầu do ds đã sx
        FileNode* current = head;
        FileNode* prev = nullptr; //Node đứng trước node min

        while (current) {
            if (current->size == smallest->size && current->timestamp < smallest->timestamp) {
                smallest = current;
            }
            prev = current;
            current = current->next;
        }

        if (smallest == head) { 
            deleteFromHead(); 
        } else {
            current = head;
            while (current->next != smallest) {
                current = current->next;
            }
            deleteAfterNode(current);
        }
    }

    //Hiển thị ds file
    void displayFiles() {
        FileNode* current = head;
        while (current) {
            std::cout << "File: " << current->fileName 
                      << ", Size: " << current->size << "MB"
                      << ", Timestamp: " << current->timestamp << std::endl;
            current = current->next;
        }
    }
};

int main() {
    FileList folder;

    //Thêm file vào ds
    folder.addFileSorted("file1.txt", 500, "2021-01-01");
    folder.addFileSorted("file2.txt", 300, "2020-12-31");
    folder.addFileSorted("file3.txt", 500, "2020-01-01");
    folder.addFileSorted("file4.txt", 200, "2022-01-01");

    std::cout << "Danh sách file ban đầu:\n";
    folder.displayFiles();

    //Xóa file min và lưu lâu nhất
    folder.deleteSmallestAndOldest();
    std::cout << "\nSau khi xóa file nhỏ nhất và lưu lâu nhất:\n";
    folder.displayFiles();

    //Xóa file ở đầu ds
    folder.deleteFromHead();
    std::cout << "\nSau khi xóa file ở đầu danh sách:\n";
    folder.displayFiles();

    //Xóa file ở cuối ds
    folder.deleteFromTail();
    std::cout << "\nSau khi xóa file ở cuối danh sách:\n";
    folder.displayFiles();

    return 0;
}
