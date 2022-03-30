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

        bool    isFdInSet(int fd);
        void    updateFdSet(void);
        void    zeroFdSet(void);

    public:
        MultiClientHandler(void);
        ~MultiClientHandler(void);

        void    addFdToSet(int fd);
        void    clearFd(int fd);

        bool    isFdReadyToCommunicate(int fd);

        size_t  getFdmax() const;

        class UpdateFailed : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

std::ostream&   operator<<(std::ostream& o, MultiClientHandler const& src);

#endif