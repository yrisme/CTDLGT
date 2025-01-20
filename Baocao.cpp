/*
  Mô tả giải thuật Dijkstra:
  
  - Thuật toán Dijkstra tìm đường đi ngắn nhất từ một đỉnh nguồn đến tất cả các đỉnh khác trong đồ thị có trọng số không âm.
  - Thuật toán sử dụng một hàng đợi ưu tiên (min-heap) để chọn đỉnh có khoảng cách nhỏ nhất chưa được xử lý.

  Các bước thực hiện:

  1. Khởi tạo:
     - Đặt khoảng cách từ đỉnh nguồn đến chính nó là 0.
     - Tất cả các đỉnh khác có khoảng cách ban đầu là vô cùng (INT_MAX).
     - Tạo một hàng đợi ưu tiên để lưu trữ các đỉnh và khoảng cách tương ứng.

  2. Thực hiện vòng lặp:
     - Chọn đỉnh có khoảng cách nhỏ nhất từ hàng đợi ưu tiên.
     - Đánh dấu đỉnh này là đã xử lý.
     - Thực hiện relaxation trên tất cả các đỉnh kề:
     - Nếu khoảng cách mới đến đỉnh kề nhỏ hơn khoảng cách hiện tại, cập nhật giá trị.
     - Thêm đỉnh kề vào hàng đợi ưu tiên với khoảng cách mới.

  3. Dừng thuật toán:
     - Khi tất cả các đỉnh đã được xử lý hoặc hàng đợi trống.

  4. Truy vết đường đi:
     - Sử dụng mảng prev để lưu đỉnh trước đó trên đường đi ngắn nhất từ nguồn.

  Mã giả chi tiết:

  Hàm Dijkstra(Đồ thị, Đỉnh nguồn):
      1. Khởi tạo khoảng cách từ nguồn đến tất cả các đỉnh là vô cùng (∞)
      2. Đặt khoảng cách từ nguồn đến nguồn là 0
      3. Tạo một hàng đợi ưu tiên (min-heap) và thêm đỉnh nguồn với khoảng cách 0
      4. Trong khi hàng đợi không rỗng:
          a. Lấy đỉnh có khoảng cách nhỏ nhất (currentNode) ra khỏi hàng đợi
          b. Với mỗi đỉnh kề của currentNode:
              i. Tính khoảng cách mới = khoảng cách đến currentNode + trọng số cạnh
              ii. Nếu khoảng cách mới < khoảng cách hiện tại của đỉnh kề:
                  Cập nhật khoảng cách của đỉnh kề = khoảng cách mới
                  Cập nhật đỉnh trước đó của đỉnh kề = currentNode
                  Thêm đỉnh kề vào hàng đợi với khoảng cách mới
      5. Trả về mảng khoảng cách và mảng đỉnh trước đó

  Ví dụ minh họa:
  
  Input:
  Đồ thị với các cạnh:
    {0, 1, 10}, {0, 4, 3}, {1, 2, 2}, {1, 4, 4},
    {2, 3, 9}, {3, 2, 7}, {4, 1, 1}, {4, 2, 8}, {4, 3, 2}
  Số đỉnh: 5

  Output:
  - Từ đỉnh nguồn 0:
    Path (0 -> 1): Minimum cost = 4, Route = [0, 4, 1]
    Path (0 -> 2): Minimum cost = 6, Route = [0, 4, 1, 2]
    Path (0 -> 3): Minimum cost = 5, Route = [0, 4, 3]
    Path (0 -> 4): Minimum cost = 3, Route = [0, 4]

  - Tương tự với các đỉnh nguồn khác.
*/

#include <iostream> 
#include <vector>   
#include <queue>   
#include <climits> 

//CTDL biểu diễn một cạnh trong đồ thị
struct Edge {
    int source, dest, weight; 
};

//CTDL biểu diễn một đỉnh trong hàng đợi ưu tiên
struct Node {
    int vertex, weight; 
};

//Hàm so sánh cho hàng đợi ưu tiên
struct comp {
    bool operator()(const Node &lhs, const Node &rhs) const {
        return lhs.weight > rhs.weight; //Đỉnh có khoảng cách nhỏ hơn được ưu tiên
    }
};

//Lớp biểu diễn đồ thị dưới dạng danh sách kề
class Graph {
public:
    std::vector<std::vector<Edge>> adjList; 

    //Hàm dựng để khởi tạo đồ thị từ danh sách các cạnh
    Graph(const std::vector<Edge> &edges, int n) {
        adjList.resize(n);
        for (const Edge &edge : edges) {
            adjList[edge.source].push_back(edge); //Thêm cạnh vào danh sách kề
        }
    }
};

//Hàm đệ quy in đường đi từ nguồn đến đỉnh đích
void printPath(const std::vector<int> &prev, int i, int source) {
    if (i < 0) return; // Dừng nếu không có đường đi
    printPath(prev, prev[i], source); //Đệ quy in đỉnh trước đó
    if (i != source) std::cout << ", "; //Thêm dấu phẩy giữa các đỉnh
    std::cout << i; // In đỉnh hiện tại
}

//Hàm thực hiện thuật toán Dijkstra để tìm đường đi ngắn nhất
void findShortestPaths(const Graph &graph, int source, int n) {
    //Hàng đợi ưu tiên để lưu các đỉnh với khoảng cách tương ứng
    std::priority_queue<Node, std::vector<Node>, comp> minHeap;
    minHeap.push({source, 0}); //Thêm đỉnh nguồn vào hàng đợi với khoảng cách 0

    std::vector<int> dist(n, INT_MAX); //Mảng lưu khoảng cách ngắn nhất từ nguồn
    dist[source] = 0; //Khoảng cách từ nguồn đến chính nó là 0

    std::vector<bool> done(n, false); //Mảng đánh dấu đỉnh đã xử lý
    std::vector<int> prev(n, -1); //Mảng lưu đỉnh trước đó trên đường đi ngắn nhất

    while (!minHeap.empty()) {
        Node node = minHeap.top(); //Lấy đỉnh có khoảng cách nhỏ nhất
        minHeap.pop(); //Loại đỉnh ra khỏi hàng đợi

        int u = node.vertex; //Đỉnh hiện tại

        if (done[u]) continue; //Nếu đã xử lý, bỏ qua
        done[u] = true; //Đánh dấu đỉnh đã xử lý

        for (const auto &edge : graph.adjList[u]) {
            int v = edge.dest, weight = edge.weight; //Đỉnh kề và trọng số cạnh

            //Nếu tìm được khoảng cách ngắn hơn, cập nhật
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight; //Cập nhật khoảng cách
                prev[v] = u; //Lưu đỉnh trước đó
                minHeap.push({v, dist[v]}); //Thêm đỉnh kề vào hàng đợi
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (i != source && dist[i] != INT_MAX) {
            std::cout << "Path (" << source << " -> " << i << "): Minimum cost = "
                      << dist[i] << ", Route = [";
            printPath(prev, i, source); 
            std::cout << "]\n";
        }
    }
}

int main() {
    //Danh sách các cạnh của đồ thị
    std::vector<Edge> edges = {
        {0, 1, 10}, {0, 4, 3}, {1, 2, 2}, {1, 4, 4},
        {2, 3, 9}, {3, 2, 7}, {4, 1, 1}, {4, 2, 8}, {4, 3, 2}
    };

    int n = 5; //Số đỉnh trong đồ thị
    Graph graph(edges, n); //Khởi tạo đồ thị

    //Thực hiện thuật toán Dijkstra từ mỗi đỉnh nguồn
    for (int source = 0; source < n; source++) {
        std::cout << "Source: " << source << "\n";
        findShortestPaths(graph, source, n);
        std::cout << std::endl;
    }

    return 0;
}
