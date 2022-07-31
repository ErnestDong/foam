---
tags: blockchain
---
# 智能合约

是运行在[[ethereum]]上的代码，它们仅在由用户(或另一个 [[smart contract]])的事务触发时才执行。一旦智能合同发布到以太坊，只要以太坊存在，它就会一直在线并运行。由于智能合同是自动化的，它们不歧视任何用户，随时可以使用。

智能合约不仅是开放源码库，而且它们基本上是运行 24/7 的开放应用程序接口服务，不能被取消。 智能合约提供了为用户和应用程序（去中心化应用程序）之间交互的公开方法，无需许可。 任何应用程序都可能会与已部署的智能合约集成组成功能，如添加数据源或支持代币交换。 任何人都可以在以太坊上部署智能合约，以便添加自定义功能来满足其应用程序的需要。

## dapp

DAPP 开发的好处

- **零停机时间** – 一旦将某 dapp 的[[smart contract]]部署到区块链上，整个网络都能为那些希望与合约互动的客户提供服务。 因此，恶意参与者无法针对单个 dapp 发起 DoS 攻击。
- **隐私** – 您不需要提供真实世界的身份来部署或与 dapp 进行交互。
- **抵制审查** – 网络上没有任何一个实体可以阻止用户提交交易、部署 dapp 或读取区块链上的数据。
- **数据完整性** – 由于采用了加密基元，存储在区块链上的数据是不可更改和无可争议的。 恶意行为者无法伪造已经公开的交易或其他数据。
- **无需信任的计算/可验证的行为** – 智能合约可以分析并保证以可预测的方式执行，而无需信任中心化组织。 这在传统模式下是不存在的，比如我们使用网上银行系统时，我们要相信金融机构不会滥用我们的金融数据，不会篡改记录，也不会被黑客攻击。

坏处是

- **维护** – dapp 可能更难维护，因为发布到区块链的代码和数据更难修改。 在部署后，开发人员很难对去中心化应用程序（或其存储的底层数据）进行更新，即使在旧版本中发现了漏洞或安全风险。
- **性能开销** – 巨大的性能开销，而且难以扩展更多性能。 为了达到以太坊所追求的安全、完整、透明和可靠的水平，每个节点都会运行和存储每一笔交易。 除此之外，工作量证明也需要时间。 粗略计算，开销会达到目前标准计算的 1,000,000 倍左右。
- **网络拥塞** – 至少在当前模型中，如果一个 dapp 使用了太多的计算资源，整个网络都会承担影响。 目前，该网络每秒只能处理约 10 笔交易；如果交易发送的速度超过这个速度，未确认的交易池会迅速膨胀。
- **用户体验** – 设计用户友好的体验可能更难。普通终端用户可能会发现，很难以真正安全的方式设置与区块链互动所需的工具堆栈。
- **集中化** — 无论如何，建立在以太坊基础层之上的用户友好型和开发人员友好型解决方案最终看起来都像集中式服务。 例如，这种服务可以在服务器端存储密钥或其他敏感信息，使用中心化服务器为前端服务，或在写到区块链之前在中心化服务器上运行重要的业务逻辑。 这消除了区块链与传统模式相比的许多（并不是全部）优势。

[//begin]: # "Autogenerated link references for markdown compatibility"
[ethereum]: ethereum.md "ethereum"
[smart contract]: <smart contract.md> "智能合约"
[//end]: # "Autogenerated link references"