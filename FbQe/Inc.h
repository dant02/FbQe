#include "pch.h"

using namespace std;
using namespace Firebird;

namespace FbQe {
    struct Result
    {
        int result;
        bool resultNull;
    };

    class IncEx : public IExternalFunctionImpl<IncEx, ThrowStatusWrapper> {
    public:
        void dispose() override;
        void getCharSet(ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize) override;
        void execute(ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg) override;
    };

    class IncFactory : public IUdrFunctionFactoryImpl<IncFactory, ThrowStatusWrapper> {
    public:
        IncFactory(ostream* log);
        ~IncFactory();

        void dispose() override;
        void setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) override;
        IExternalFunction* newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) override;
    private:
        ostream* fLog;
    };
}