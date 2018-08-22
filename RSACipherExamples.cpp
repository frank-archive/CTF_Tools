#include"RSACipher.h"
#include<iostream>
#include<string>
using namespace std;

void RSAExamples() {
	PUBKEY a = parsePublicKey("MDwwDQYJKoZIhvcNAQEBBQADKwAwKAIhAL/plnUgiIhfLqI1L98+lRX2YvxNNHXdpvihYI5UtBa3AgMBAAE=");
	cout << "bits:" << a.bits << endl << "public_e:" << a.publicExponent.toString() << endl;
	cout << "modulus:" << a.modulus.toString() << endl;
	std::pair<BigInteger, BigInteger>ret = factorize(a.modulus);
	cout << ret.first.toString() << endl << ret.second.toString() << endl;

	PRIVKEY b = parsePrivateKey("MIICXQIBAAKBgQC8C1raL9WGWd5y5SQF+nfgvakjcDrTjGsN6MXrX7lJRiZq4aFMivIv62ThF/f4J2sJewy8qOunTCByVpbTCqqm0aCkpwszYGXiweEM2DdfwmBUfitBNW+SsBboH64bQu7E2jbqylpZfP2uriypPJRGx74rbtqpTh7dKBgfuXpIxwIDAQABAoGBAJTvnWbAiiseFN0FdfGyPq5nKYajBkS1q7jZi6DwMS3C/PycdofMaSPhGgZaWJFYjyN0LVNjqznXRr+oq0693Qhj9oSyp5TxGjTUJ3h+eMR+2LLV2Z0EtW0eZy6wJs6jiyM3WmLCMpqK/44ON3ethlU8MQB5PXU/UBrU1ivEmOThAkEA87/TvDist49U4xf9B+ftf+q0RJm/eb+/vWYdd6NZPQOueLG62lkqCkl9vULmGQxp3Feasw4pvTR/ZNEFew+3cQJBAMV+zmBh89fq0dcC4VDpx8VPxm88Lj/UcvqjqtqYsarOuu5oJIwA8ejpPkr3jWfjArNBN78FCkRXU3IQbfBzF7cCQF6XjfrYX6aol/+9OnPL/K4MjkKlC9qaoDVHIJ5iJOp5uEacam/79EWjuYkuIg+McrSQxrdAAtCrQ9kDCMZ2FfECQB/6rIhG1Ck+SMQ8Hyfu8v4sMMGKSSLkz8lt/xhuaTZzSymXi3NwI7vHKOMSur77r1A/Wzt/IW53hXeO2X555HkCQQDEJT3vVVYjsgoiiv12UsDi8ASUGf3MSn2Th95uWpzpzO2u34c4VDDsuPb1DtKe/TtQ0Ua4hTpm+fgyMOV4qzVQ");
	cout << "bits:" << b.bits << endl << "exp1:" << b.exponent1.toString() << endl << "exp2:" << b.exponent2.toString() << endl << "modulus:" << b.modulus.toString() << endl;
}