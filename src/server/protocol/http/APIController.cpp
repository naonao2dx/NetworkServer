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
    if (m_enableMethodSet.count(m_httpRequest.getMethod()) == 0) {
        m_httpResponse.setStatusCode(405);
        return;
    }

    // API server usually response status 200, regardless of uri status.
    m_httpResponse.setStatusCode(200);
}

void APIController::responseBody() {
    if (m_httpResponse.getStatusCode() == 200) {


        std::string message("This message is output from C++ API program !");

        addResponse(m_connfd, message.data(), message.size());
    }
}