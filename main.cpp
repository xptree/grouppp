#include "group.h"
#include "util.h"
#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/PatternLayout.hh"

using namespace std;

int main()
{
	//log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &cout);
	log4cpp::Appender *osAppender = new log4cpp::FileAppender("default", "program.log");
    log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
    pLayout->setConversionPattern("%d: %p %c %x: %m%n");
    osAppender->setLayout(pLayout);
    log4cpp::Category& root = log4cpp::Category::getRoot();
    log4cpp::Category& infoCategory = root.getInstance("infoCategory");
    infoCategory.addAppender(osAppender);
    infoCategory.setPriority(log4cpp::Priority::INFO);
	/*
     * infoCategory.info("system is running");
     * infoCategory.warn("system has a warning");
     * infoCategory.error("system has a error, can't find a file");
     * infoCategory.fatal("system has a fatal error,must be shutdown");
     * infoCategory.info("system shutdown,you can find some information in system log");
	 */
	Group group("../Data/user1m", "../Data/edge1m");
	group.clean();
	group.member(10,1000000);
	group.dump("output.txt");
    log4cpp::Category::shutdown();
	return 0;
}
