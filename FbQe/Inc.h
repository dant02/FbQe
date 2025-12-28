#pragma once
#include "pch.h"
#include "log.h"
#include <msclr/gcroot.h>

namespace FbQe {
    using namespace std;
    using namespace Firebird;

    struct Result {
        int R;
        DbNullFlag RNull;
    };

    class IncEx : public IExternalFunctionImpl<IncEx, ThrowStatusWrapper> {
    public:
        IncEx();
        ~IncEx();
        void dispose() override;
        void getCharSet(ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize) override;
        void execute(ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg) override;
    };

    class IncFactory : public IUdrFunctionFactoryImpl<IncFactory, ThrowStatusWrapper> {
    public:
        explicit IncFactory();
        ~IncFactory() final;
        void dispose() override;
        void setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) override;
        IExternalFunction* newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) override;
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
    private:
        const msclr::gcroot<System::DateTime> fFirebirdEpoch = System::DateTime(1858, 11, 17, 0, 0, 0);
    };

    class GetCurrentTimestampUTC_Factory : public IUdrFunctionFactoryImpl<GetCurrentTimestampUTC_Factory, ThrowStatusWrapper> {
    public:
        explicit GetCurrentTimestampUTC_Factory() = default;
        void dispose() override;
        void setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) override;
        IExternalFunction* newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) override;
    private:
        unique_ptr<GetCurrentTimestampUTC> fFunction = nullptr;
    };
}
