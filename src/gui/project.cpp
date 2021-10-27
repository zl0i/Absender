#include "project.h"

Project::Project(QJsonObject)
{

    MockServer *server = new MockServer();

    MockResponse res("{\"result\": \"ok\"}", {
                         {"Content-Type", "application/json"}
                     });
    MockEndpoint *ep1 = new MockEndpoint("/", "GET", res);
    MockEndpoint *ep2 = new MockEndpoint("/users", "GET", MockResponse("{\"users\": []}", {{"Content-Type", "application/json"}}));
    MockEndpoint *ep3 = new MockEndpoint("/points", "GET", MockResponse("", {{"Content-Type", "application/json"}}, 404));

    MockHost *host = new MockHost("test.com");

    host->addEndpoint(ep1);
    host->addEndpoint(ep2);
    host->addEndpoint(ep3);

    server->addHost(host);
    //server.start();

    _mocks->append(server);
    _mocks->append(new MockServer());
}
