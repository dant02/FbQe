#include "pch.h"
#include "log.h"

using namespace std;
using namespace Firebird;

namespace FbQe {
    struct Result {
        int Result;
        bool resultNull;
    };

    struct Input {
        int val;
        bool valNull;
    };

    class IncEx : public IExternalFunctionImpl<IncEx, ThrowStatusWrapper> {
    public:
        IncEx(Log* aLog);
        ~IncEx();
        void dispose() override;
        void getCharSet(ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize) override;
        void execute(ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg) override;
    private:
        Log* fL;
    };

    class IncFactory : public IUdrFunctionFactoryImpl<IncFactory, ThrowStatusWrapper> {
    public:
        IncFactory(Log* aLog);
        ~IncFactory();
        void dispose() override;
        void setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) override;
        IExternalFunction* newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) override;
    private:
        Log* fL;
    };
}
