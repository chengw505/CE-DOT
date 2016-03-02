// smtp-tls.cpp : Defines the entry point for the console application.
//

#include "stdio.h"

#include "curl\curl.h"

#define MY_USERNAME     "chengw505@yahoo.com"
#define MY_PASSWORD     "4UNMCEDOT"
#define MYSMPT_URL      "smtp.mail.yahoo.com:587"

#define FROM            "<chengw505@yahoo.com>"
#define TO              "<chengw505@gmail.com>"
#define CC              FROM

static char payload_body[4096 * 2 + 512];

static char *payload_text[] = {
    "To: " TO "\r\n",
    "From: " FROM "(TracsDataReport)\r\n",
    "Cc:" CC "\r\n",
    "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
    "Subject: TracsData Import Report\r\n",
    "\r\n", /* empty line to divide headers from body, see RFC5322 */
    payload_body,
    NULL
};

struct upload_status {
    int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = payload_text[upload_ctx->lines_read];

    if (data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;

        return len;
    }

    return 0;
}

int sendEmail(char* szBody)
{
    _snprintf_s(payload_body, sizeof(payload_body), "%s\r\n", szBody);

    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if (curl)
    {
        /* Set username and password */
        curl_easy_setopt(curl, CURLOPT_USERNAME, MY_USERNAME);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, MY_PASSWORD);
        curl_easy_setopt(curl, CURLOPT_URL, MYSMPT_URL);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

        recipients = curl_slist_append(recipients, TO);
        //recipients = curl_slist_append(recipients, CC);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "./curl-ca-bundle.crt");

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Send the message */
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        /* Always cleanup */
        curl_easy_cleanup(curl);
    }

    return 0;
}


