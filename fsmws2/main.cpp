#include <cppcms/applications_pool.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_response.h>
#include <cppcms/application.h>
#include <cppcms/url_mapper.h>
#include <cppcms/service.h>

class MainApp : public cppcms::application{
public:
  //-------------------------------------------------------------------------------------
  // Dsc: Конструктор, который будет запушен во время старта программы
  //-------------------------------------------------------------------------------------
  MainApp(cppcms::service &s) : cppcms::application(s)
  {}
  //-------------------------------------------------------------------------------------
  // Dsc: Функция в которую мы попадем, если иного не указано в конструкторе
  //      ( об этом позже )
  //-------------------------------------------------------------------------------------
  virtual void main(std::string path)
  {
    response().out() << "Hello!";
  }
};

int main(int argc, char **argv)
{
	try {
        // создаем сервис
        cppcms::service srv(argc,argv);
        // задаем корень
        srv.applications_pool().mount(cppcms::applications_factory<MainApp>());
        // запускаем
        srv.run();
    }
    catch(std::exception const &e) {
    std::cerr << "Failed: " << e.what() << std::endl;
    std::cerr << booster::trace(e) << std::endl;
    return 1;
    }
    return 0;
}