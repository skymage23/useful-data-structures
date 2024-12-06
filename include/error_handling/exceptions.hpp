#ifndef USEFUL_DATA_STRUCTURES_EXCEPTIONS
#define USEFUL_DATA_STRUCTURES_EXCEPTIONS
namespace useful_data_structures {
    namespace error_handling {
        //Hello:
        class NotImplementedException : std::logic_error {
            //Hello:
            public:
            NotImplementedException() : std::logic_error("Logic has yet to be implemented"){}
        };
    };
};
#endif
