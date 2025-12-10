#pragma once
#include "pch.h"
#include "log.h"

namespace FbQe {
    using namespace std;
    using namespace Firebird;

    struct Result {
        int R;
        DbNullFlag RNull;
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
        explicit IncFactory(Log* aLog);
        ~IncFactory() final;
        void dispose() override;
        void setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) override;
        IExternalFunction* newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) override;
    private:
        Log* fL;
    };

    struct TimestampResult {
        ISC_TIMESTAMP R;
        DbNullFlag RNull;
    };

    class GetCurrentTimestampUTC : public IExternalFunctionImpl<GetCurrentTimestampUTC, ThrowStatusWrapper> {
    public:
        explicit GetCurrentTimestampUTC() = default;
        void dispose() override;
        void getCharSet(ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize) override;
        void execute(ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg) override;
    };

    class GetCurrentTimestampUTC_Factory : public IUdrFunctionFactoryImpl<GetCurrentTimestampUTC_Factory, ThrowStatusWrapper> {
    public:
        explicit GetCurrentTimestampUTC_Factory() = default;
        void dispose() override;
        void setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) override;
        IExternalFunction* newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) override;
    };
}
