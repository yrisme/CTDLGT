#include <iostream>
#include <string>
#include <ctime>

struct FileNode {
    std::string fileName;     //Tên file
    size_t fileSize;          //Kích thước file
    time_t creationTime;      //Tgian tạo file
    FileNode* next;           //Trỏ đến node kế

    FileNode(std::string name, size_t size, time_t time)
        : fileName(name), fileSize(size), creationTime(time), next(nullptr) {}
};

struct FileList {
    FileNode* head;

    FileList() : head(nullptr) {}

    //Thêm file mới vào ds theo trình tự tgian
    void addFile(std::string name, size_t size, time_t time) {
        FileNode* newNode = new FileNode(name, size, time);
        if (head == nullptr || head->creationTime > time) {
            newNode->next = head;
            head = newNode;
        } else {
            FileNode* current = head;
            while (current->next != nullptr && current->next->creationTime <= time) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    //Hàm tính tổng các file trong ds
    size_t calculateTotalSize() const {
        size_t totalSize = 0;
        FileNode* current = head;
        while (current != nullptr) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }

    //Hàm xóa các file nhỏ nhất cho đến khi đủ dung lượng 
    void trimFilesForUSB(size_t usbSize) {
        while (calculateTotalSize() > usbSize) {
            if (head == nullptr) return;

            //Tìm file nhỏ nhất
            FileNode* minNode = head;
            FileNode* prevMin = nullptr;
            FileNode* current = head;
            FileNode* prev = nullptr;
            while (current != nullptr) {
                if (current->fileSize < minNode->fileSize) {
                    minNode = current;
                    prevMin = prev;
                }
                prev = current;
                current = current->next;
            }

            //Xóa file nhỏ nhất khỏi ds
            if (prevMin == nullptr) {
                head = head->next;
            } else {
                prevMin->next = minNode->next;
            }
            delete minNode;
        }
    }

    //Hiển thị ds file
    void displayFiles() const {
        FileNode* current = head;
        while (current != nullptr) {
            std::cout << "Tên file: " << current->fileName
                      << ", Kích thước: " << current->fileSize
                      << " bytes, Thời gian tạo: " << current->creationTime << std::endl;
            current = current->next;
        }
    }
};

int main() {
    FileList fileList;
    size_t usbSize = 32 * 1024 * 1024 * 1024; 

    //Thêm các file vào ds 
    fileList.addFile("file1.txt", 1000, 1000000000);
    fileList.addFile("file2.txt", 5000, 1300000000);
    fileList.addFile("file3.txt", 2000, 1100000000);
    fileList.addFile("file4.txt", 3000, 1200000000);
    fileList.addFile("file5.txt", 1500, 1100000000);

    //Hiển thị ds file ban đầu
    std::cout << "Danh sách file ban đầu:\n";
    fileList.displayFiles();

    //Tính tổng kích thước các file
    size_t totalSize = fileList.calculateTotalSize();
    std::cout << "\nTổng kích thước các file: " << totalSize << " bytes\n";

    //Lưu vào USB 32GB và xóa các file nhỏ nhất
    if (totalSize > usbSize) {
        fileList.trimFilesForUSB(usbSize);
    }

    //Hiển thị danh sách file sau khi loại bỏ 
    std::cout << "\nDanh sách file sau khi xóa để phù hợp với dung lượng USB:\n";
    fileList.displayFiles();

    return 0;
}
