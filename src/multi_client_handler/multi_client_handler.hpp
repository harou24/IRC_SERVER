#ifndef MULTI_CLIENT_HANDLER_HPP
# define MULTI_CLIENT_HANDLER_HPP

# include <sys/select.h>
# include <iostream>
# include <stdexcept>
# include <cstring>
# include <cerrno>

class MultiClientHandler {

    public:
        MultiClientHandler(void);
        ~MultiClientHandler(void);

        void        addFdToSet(int fd);
        void        clearFd(int fd);

        bool        isFdReadyToCommunicate(int fd);

        size_t      getFdmax() const;
    
    private:
        bool        isFdInSet(int fd);
        void        updateFdSet(void);
        void        zeroFdSet(void);

    private:
        fd_set      tmpFds_;
        fd_set      mainFds_;
        std::size_t fdMax_;
        timeval     timer_;
};

std::ostream&   operator<<(std::ostream& o, MultiClientHandler const& src);

#endif