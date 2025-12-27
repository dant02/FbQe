#include "pch.h"
#include "Inc.h"
#include <ctime>

namespace FbQe {
    IncEx::IncEx() {
    }

    IncEx::~IncEx() {
    }

    void IncEx::dispose() {
    }

    void IncEx::getCharSet(Firebird::ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize) {
    }

    void IncEx::execute(Firebird::ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg) {
        auto output = (struct Result*)outMsg;
        output->RNull = 0;
        output->R = 1;
    }

    IncFactory::IncFactory() {
    }

    IncFactory::~IncFactory() {
    }

    void IncFactory::dispose() {
    }

    void IncFactory::setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) {
    }

    IExternalFunction* IncFactory::newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) {
        return new IncEx();
    }

    //// GetCurrentTimestampUTC

    void GetCurrentTimestampUTC::dispose() {
        // what to add ?
    }

    void GetCurrentTimestampUTC::getCharSet(Firebird::ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize) {
        // what to add ?
    }

    void GetCurrentTimestampUTC::execute(Firebird::ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg) {
        using namespace std::chrono;
        const duration utc_now = system_clock::now().time_since_epoch();                  // depends on system clock to be UTC
        const int64_t utc_now_탎 = duration_cast<microseconds>(utc_now).count();
        const int64_t utc_time_of_day_탎 = utc_now_탎 % MICROSECONDS_IN_DAY;
        const int64_t utc_date_days = (utc_now_탎 - utc_time_of_day_탎) / MICROSECONDS_IN_DAY;
        auto output = (struct TimestampResult*)outMsg;
        output->RNull = 0;
        output->R.timestamp_date = (int)utc_date_days + 40587;                            // Win11,2025: add day difference of system clock epoch and Firebird SQL epoch
        output->R.timestamp_time = (unsigned int)(utc_time_of_day_탎 / 100);
    }

    void GetCurrentTimestampUTC_Factory::dispose() {
        this->fFunction.reset();
    }

    void GetCurrentTimestampUTC_Factory::setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) {
        this->fFunction = make_unique<GetCurrentTimestampUTC>();
    }

    IExternalFunction* GetCurrentTimestampUTC_Factory::newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) {
        return this->fFunction.get();
    }
}