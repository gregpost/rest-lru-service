#include <cstdlib>
#include <drogon/drogon.h>

using namespace drogon;

typedef std::function<void(const HttpResponsePtr &)> Callback;

void nameHandler(const HttpRequestPtr &request, Callback &&callback) {
    Json::Value jsonBody;
    auto requestBody = request->getJsonObject();

    if (requestBody == nullptr) {
        jsonBody["status"] = "error";
        jsonBody["message"] = "body is required";

        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }

    if (!requestBody->isMember("name")) {
        jsonBody["status"] = "error";
        jsonBody["message"] = "field `name` is required";

        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }

    auto name = requestBody->get("name", "guest").asString();

    jsonBody["message"] = "Hello, " + name + "!";

    auto response = HttpResponse::newHttpJsonResponse(jsonBody);
    callback(response);
}

int main() {
    app()
        .loadConfigFile("./config.json")
        // Регистрируем обработчик nameHandler
        // для запроса
        // POST /name
        .registerHandler("/name", &nameHandler, {Post})
        .run();

    return EXIT_SUCCESS;
}




#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;
 
class LRUCache {
 
private:
    int capacity;
    list<int> cache;
    unordered_map<int, list<int>::iterator> map;
 
public:
    LRUCache(int capacity) : capacity(capacity) { }
 
      // This function returns false if key is not
    // present in cache. Else it moves the key to
    // front by first removing it and then adding
    // it, and returns true.
    bool get(int key) {
        auto it = map.find(key);
        if (it == map.end()) {
            return false;
        }
        cache.splice(cache.end(), cache, it->second);
        return true;
    }
 
    void refer(int key) {
        if (get(key)) {
            return;
        }
        put(key);
    }
 
    // displays contents of cache in Reverse Order
    void display() {
        for (auto it = cache.rbegin(); it != cache.rend(); ++it) {
           
         // The descendingIterator() method of
        // java.util.LinkedList class is used to return an
        // iterator over the elements in this LinkedList in
        // reverse sequential order
            cout << *it << " ";
        }
    }
 
    void put(int key) {
        if (cache.size() == capacity) {
            int first_key = cache.front();
            cache.pop_front();
            map.erase(first_key);
        }
        cache.push_back(key);
        map[key] = --cache.end();
    }
};
 
int main() {
    LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(1);
    cache.refer(4);
    cache.refer(5);
    cache.display();
    return 0;
}
 
// This code is contributed by divyansh2212