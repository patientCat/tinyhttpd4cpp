
#include "../HttpRequest.hh"
#include "../HttpResponse.hh"
#include <functional>

namespace  singsing{
using HttpHandler = std::function<void(const HttpRequest& req, HttpResponse *response)>;
}
