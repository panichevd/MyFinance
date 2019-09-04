#ifndef IPERSISTENCEPROVIDER_H
#define IPERSISTENCEPROVIDER_H


class IPersistenceProvider
{
public:
    IPersistenceProvider() = default;
    virtual ~IPersistenceProvider() = default;

    virtual bool read_data() = 0;

    // TODO: virtual const QVector<std::unique_ptr<Account>> & accounts() = 0;
};

#endif // IPERSISTENCEPROVIDER_H
