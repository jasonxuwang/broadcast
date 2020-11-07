#include "Logger.h"



void Logger::setfile(std::string filename){
    // concat folder and filename 
    m_fout.open(filename+LOG_FOLDER);
    log("Logger started", INFO);
}

Logger::~Logger(){
    

}

Logger::Logger(){
    m_log_level_map[-1] = "[DEBUG] ";
    m_log_level_map[0] = "[INFO] ";
    m_log_level_map[1] = "[WARN] ";
    m_log_level_map[2] = "[ERROR] ";

}


void Logger::close(){
    m_fout.close();
}


int32_t Logger::log( std::string out , Log_Level iLogLevel){

    // process message
    if (iLogLevel >= LOG_PRINT_ABOVE) { // if greater than print level
         std::cout <<  m_log_level_map[iLogLevel]+  out <<std::endl;     
    }

    if (iLogLevel >= LOG_SAVE_ABOVE ){ // only write level >= INFO to file
        m_fout <<  m_log_level_map[iLogLevel]+  out << std::endl <<std::flush;
    }

    return 0;

}