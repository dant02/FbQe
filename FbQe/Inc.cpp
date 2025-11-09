#include "pch.h"
#include "Inc.h"

namespace FbQe {
    void IncEx::dispose()
    {
    }

    void IncEx::getCharSet(Firebird::ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize)
    {
    }

    void IncEx::execute(Firebird::ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg)
    {
        auto output = (Result*)outMsg;
        output->result = 1;
    }

    void IncFactory::dispose()
    {
    }

    void IncFactory::setup(Firebird::ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder)
    {
    }

    IExternalFunction* IncFactory::newItem(Firebird::ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata)
    {
        return new IncEx();
    }
}