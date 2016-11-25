#include <stdlib.h>
#include <time.h>
#include "php_mio_logger.h"

/*
 * @param log_file, log_content
 * @return int
*/
int write_log(const char *log_file, const char *channel, const char *level, const char *log_content)
{
    int ret,
        i,
        j,
        time_len,
        channel_len,
        level_len,
        log_len,
        lf_i;

    FILE *fd = NULL;

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char time_str[255] = {};
    sprintf(time_str, "[%4d-%2d-%2d %2d:%2d:%2d]", 
            1900 + timeinfo->tm_year, 
            1 + timeinfo->tm_mon,
            timeinfo->tm_mday,
            timeinfo->tm_hour,
            timeinfo->tm_min,
            timeinfo->tm_sec);

    channel_len = strlen(channel);
    level_len = strlen(level);
    log_len = strlen(log_content);
    time_len = strlen(time_str);

    char *str_buf = (char *)malloc(time_len + 1 + channel_len + 1 + level_len + 1 + log_len + 2);

    /** Open file **/
    if ((fd = fopen(log_file, "ab+")) == NULL) {
        return OPEN_FAILURE;
    }

    for (i = 0; i < time_len; i++) {
        *(str_buf + i) = *(time_str + i);
    }
    
    *(str_buf + i++) = '\t';

    for (j=0; j<channel_len; i++, j++) {
        *(str_buf + i) = *(channel + j);
    }
    
    *(str_buf + i++) = '.';

    for (j=0; j<level_len; i++, j++) {
        *(str_buf + i) = *(level + j);
    }
 
    *(str_buf + i++) = '\t';

    for (j=0; j<strlen(log_content); i++, j++) {
        *(str_buf + i) = *(log_content + j);
    }
    
    /** Append line feed **/
    *(str_buf + i++) = '\n';
    *(str_buf + i) = '\0';

    /** Write log content to log file **/
    if (fprintf(fd, "%s", str_buf) != strlen(str_buf)) {
        ret = WRITE_FAILURE;
        return ret;
    }

    fclose(fd);
    ret = LOG_SUCCESS;
    free(str_buf);
    return ret;
}
