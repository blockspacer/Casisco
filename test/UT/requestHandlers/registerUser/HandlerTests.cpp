#include "server/requestHandler/user/register/Handler.hpp"
#include "mocks/server/IDatabaseMock.hpp"
#include "casisco_mock.grpc.pb.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace user
{
namespace register_
{

class MockService : public Casisco::AsyncService
{
public:
    MockService()  = default;
    ~MockService() = default;

    MOCK_METHOD6(RequestregisterUser, void((::grpc::ServerContext* context, ::casisco::UserRegisterInfo* request,
                                            ::grpc::ServerAsyncResponseWriter< ::casisco::UserRegisterStatus>* response,
                                            ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag)));

    MOCK_METHOD6(RequestloginUser, void((::grpc::ServerContext* context, ::casisco::UserLoginInfo* request,
                                         ::grpc::ServerAsyncResponseWriter< ::casisco::UserLoginStatus>* response,
                                         ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag)));
};

struct HandlerShould : ::testing::Test
{
    virtual void SetUp () override
    {
        EXPECT_CALL(service_, RequestregisterUser(_, _, _, _, _, _)).Times(1).WillOnce(::testing::SaveArg<1>(&request_));
        sut_ = std::make_shared<register_::Handler>(&service_, nullptr, db_);
    }

    std::shared_ptr<register_::Handler> sut_;
    MockService service_;
    db::UsersDatabaseMock db_;
    ::casisco::UserRegisterInfo* request_;
};


TEST_F(HandlerShould, Test)
{
    EXPECT_TRUE(true);
}

} // register_
} // user
} // requestHandler
} // server
} // casisco
