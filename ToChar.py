str = "3f1b8a5cf5aa0cb148cfac766a30a78209a3ce97cb427a9e813254e0b6a99ae25370b583c275357ce3b4d6c60aafda03e99734e0e98eba56aeef821e92b8c1db43942a7c37c9977d79946fe0474df27b9cf3b12ca94bb06401d09150530bf82adfc4623bd7af97425984b8c53f51969ebc02d9b41aace79536e3282af5adedb6363d4a7bdbb06a69e24c892888f6710055bb644db60ba3b884204c03b07c2a8aca0249ac29ead77d5c879a790a09b850a55ef614cc73cf7f727223ba0d6353295c008c986aa9200349a0ac500e347ee1795a1a8369ab6151c27b1341cace56852ee76c6d3ccb8331b23cde8b224af9b2dee402d9605bbfa8401976419c57ab1686bda096b28cb654cd4a5db7c32598e01491e21b8cd54497f60fe2bc31d783928e382bfbf3332b754cf969b12aa58f438b4a57064129d4456009a172a59ab3b77cc84c76944b99a53445a529ac0a62ad490174a47324a5d34b81a682a69c0a8dd75f0de93c20e430266c23b00c4869f53c6fd0854ed3caf4544952b05ed3b3b0d6ca34f0f297f2e9a7c1187804a37a121a6ad2ab50daf475aa3a25e6c9a0d6a29def62cbd298050f5b307c053a5c8838b4c3357f3376653c3366fa6fe1025d1960c75ba643265c157a84c914d559f540c67ec1587394af7bd17830d5089d505906fa9f766a9b93909f5b6627cc05a0b2192cbfc2271b0b22d77a07ce551edaa6522d402b00003723c115936c97f54c88aa513482a05554c628e69448eb6a0ef6f346341c802bdab9b03ba0af297d9e8b938b9cabefa46722421a338a872d9a88b88c9f0eec46932c367cc58b83573d26036aaf5276e515b0f23059b40c848f638ace3703ee6c27d966990c7702ed23a0cd9ba4cf6169a668a1f0bb586b076692e1c215754ff6784bd91a248cb90f008a3eca59852c057966933a1a86b6e05b2fad91b28bc61648b041a7ac046ab8112b6ac2cb900fb5c09821dc4b0716b509e122dc97c6ed7342f6f49fb65559729c384763ba2d2bb8cf56ae36f3b269970ac54841213b24b792c949f3c775e70ac8f7cc53763ff638adc5113ec60075c1a79276ca473c113832954abe207bebf0cd0426c0e29733947256c7756bf9b50d82191a07f0ba5d5a154b0866e293473b4076a1e995f9d086a472c118ac22c216a839920660a331eee198df5b1a1595239d5780cda75f73c6765a46ae4aa34001939dfad92f7e124a5f2c628b259de9560bbf470cc69cc652dc29b93ba86a4990dce0af1a4524c199a692670caf748d16612feed711f88a505d552a6440aa0422626f185f6921a82ef925086028ae8562fc7610e1b1649ef0094d96b505fbb7f112896efac0d192af45d903ac7992bbe9bf30e2577e24581cbc4f73b180d04a69f540b39e19a4ae36aec4f21ade774965391bcaebc0af869cb63631327b421bec6726651b8758bfee73c591212d4ff981f6684c58b359c2d07fa1e601d6c5cbfdc964b31909cca37fff96204fb5688d92ca5a85758cf160e9b06ed18320a4b1b0c8e8196ae76a6f621972d17a4d64a7df04c5a4c333c3bc1acaab37709149a3b8ca082a8fbca13268a1b022230e2d630272cb9ff2e6655af17327f3b9807095f582be18bd3f4e0bb723eced69b0585629986548d722b03b5bbd157ac99dee1c0a9aa1"

e = True
cnt = 0
sCnt = 0

ret = ""

for i in str:
    if sCnt == 2368:
        break
    
    if e:
        ret += ", "
        if cnt == 32:
            cnt = 0
            ret += "\n"
        ret += "0x"
        
    cnt += 1
    sCnt += 1
    ret += i
    e = not e

print(ret)
        