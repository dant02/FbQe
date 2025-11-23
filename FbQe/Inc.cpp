#include "pch.h"
#include "Inc.h"

namespace FbQe {
    IncEx::IncEx(Log* aLog) {
        this->fL = aLog;
    }

    IncEx::~IncEx() {
        this->fL->write_line("remove IncEx");
    }

    void IncEx::dispose() {
        this->fL->write_line("IncEx.dispose");
    }

    void IncEx::getCharSet(Firebird::ThrowStatusWrapper* status, IExternalContext* context, char* name, unsigned nameSize) {
        this->fL->write_line("IncEx.getCharSet");
    }

    void IncEx::execute(Firebird::ThrowStatusWrapper* status, IExternalContext* context, void* inMsg, void* outMsg) {
        this->fL->write_line("IncEx.execute");
        auto output = (struct Result*)outMsg;
        output->RNull = 0;
        output->R = 1;
    }

    IncFactory::IncFactory(Log* aLog) {
        this->fL = aLog;
    }

    IncFactory::~IncFactory() {
        this->fL->write_line("remove IncFactory");
    }

    void IncFactory::dispose() {
        this->fL->write_line("IncFactory.dispose");
    }

    void IncFactory::setup(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata, IMetadataBuilder* inBuilder, IMetadataBuilder* outBuilder) {
        this->fL->write_line("IncFactory.setup");
    }

    IExternalFunction* IncFactory::newItem(ThrowStatusWrapper* status, IExternalContext* context, IRoutineMetadata* metadata) {
        this->fL->write_line("IncFactory.newItem");
        return new IncEx(this->fL);
    }
}