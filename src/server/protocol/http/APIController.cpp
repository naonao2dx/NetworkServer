//
// Created by 竹内 直 on 2018/03/12.
//

#include "APIController.h"
#include "../../../common/code/StrUtil.h"
#include <netinet/in.h>
#include <sstream>

APIController::APIController(int connfd, struct sockaddr *cliaddr)
: HttpController(connfd, cliaddr){

}

void APIController::setStatusCode() {
    // Non-acceptable method
    if (_enableMethodSet.count(_httpRequest.getMethod()) == 0) {
        _httpResponse.setStatusCode(405);
        return;
    }

    // API server usually response status 200, regardless of uri status.
    _httpResponse.setStatusCode(200);
}

void APIController::responseBody() {
    if (_httpResponse.getStatusCode() == 200) {


        std::string message("This message is output from C++ API program !");

        addResponse(_connfd, message.data(), message.size());
    }
}