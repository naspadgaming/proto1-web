#include <iostream>
#include "httplib.h"      // download dari: https://github.com/yhirose/cpp-httplib
using namespace std;

// Fungsi Fibonacci
int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    httplib::Server svr;

    // GET /hello
    svr.Get("/hello", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("{\"message\":\"Hello from C++ REST API\"}", "application/json");
    });

    // POST /submit
    svr.Post("/submit", [](const httplib::Request& req, httplib::Response& res) {
        string body = req.body;   // menerima data JSON
        res.set_content("{\"received\":" + body + "}", "application/json");
    });

    // GET /fibonacci/<n>
    svr.Get(R"(/fibonacci/(\d+))", [](const httplib::Request& req, httplib::Response& res) {
        int n = stoi(req.matches[1]);

        int result = fib(n);
        res.set_content("{\"result\":" + to_string(result) + "}", "application/json");
    });

    cout << "Server berjalan di http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
}
