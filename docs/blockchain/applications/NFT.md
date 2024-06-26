---
tags: blockchain
---

# NFT

非同质化[[token|代币]]（NFT）用于以唯一的方式标识某人或者某物。所有 NFT 都有一个 uint256 变量，名为 tokenId。
对于任何 ERC-721 合约，(contract address, tokenId) 是全局唯一的。

## [[solidity]] interface

```solidity
interface NFT{
    function balanceOf(address _owner) external view returns (uint256);
    function ownerOf(uint256 _tokenId) external view returns (address);
    function safeTransferFrom(address _from, address _to, uint256 _tokenId, bytes data) external payable;
    function safeTransferFrom(address _from, address _to, uint256 _tokenId) external payable;
    function transferFrom(address _from, address _to, uint256 _tokenId) external payable;
    function approve(address _approved, uint256 _tokenId) external payable;
    function setApprovalForAll(address _operator, bool _approved) external;
    function getApproved(uint256 _tokenId) external view returns (address);
    function isApprovedForAll(address _owner, address _operator) external view returns (bool);
    event Transfer(address indexed _from, address indexed _to, uint256 indexed _tokenId);
    event Approval(address indexed _owner, address indexed _approved, uint256 indexed _tokenId);
    event ApprovalForAll(address indexed _owner, address indexed _operator, bool _approved);
}
```

[//begin]: # "Autogenerated link references for markdown compatibility"
[token|代币]: ../concept/token.md "token"
[solidity]: ../concept/solidity.md "solidity"
[//end]: # "Autogenerated link references"
