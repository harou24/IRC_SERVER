#ifndef MULTI_CLIENT_HANDLER_HPP
# define MULTI_CLIENT_HANDLER_HPP

# include <sys/select.h>
# include <iostream>
# include <stdexcept>

class MultiClientHandler {
    private:
        fd_set  tmpFds;
        fd_set  mainFds;
        std::size_t fdMax;

    public:
        MultiClientHandler(void);
        ~MultiClientHandler(void);

        void    zeroFdSet(void);
        void    addFdToSet(int fd);
        void    clearFd(int fd);
        bool    isFdInSet(int fd);
        void    updateFdSet(void);

        bool    isFdReadyToCommunicate(int fd);

        class UpdateFailed : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

#endif