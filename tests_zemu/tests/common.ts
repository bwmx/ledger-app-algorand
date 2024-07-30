import { IDeviceModel } from '@zondax/zemu'
import { resolve } from 'path'

export const APP_SEED =
  'glory promote mansion idle axis finger extra february uncover one trip resource lawn turtle enact monster seven myth punch hobby comfort wild raise skin'

const APP_PATH_S = resolve('../app/output/app_s.elf')
const APP_PATH_X = resolve('../app/output/app_x.elf')
const APP_PATH_SP = resolve('../app/output/app_s2.elf')
const APP_PATH_ST = resolve('../app/output/app_stax.elf')
const APP_PATH_FL = resolve('../app/output/app_flex.elf')

export const models: IDeviceModel[] = [
  { name: 'nanos', prefix: 'S', path: APP_PATH_S },
  { name: 'nanox', prefix: 'X', path: APP_PATH_X },
  { name: 'nanosp', prefix: 'SP', path: APP_PATH_SP },
  { name: 'stax', prefix: 'ST', path: APP_PATH_ST },
  { name: 'flex', prefix: 'FL', path: APP_PATH_FL },
]

export const txAssetFreeze = [
  136, 164, 102, 97, 100, 100, 196, 32, 75, 42, 74, 217, 212, 217, 0, 234, 22, 249, 220, 238, 83, 75, 156, 1, 137, 218, 161, 172, 188, 202,
  206, 115, 215, 148, 191, 22, 139, 138, 115, 227, 164, 102, 97, 105, 100, 205, 4, 210, 163, 102, 101, 101, 205, 8, 202, 162, 102, 118, 205,
  3, 232, 162, 103, 104, 196, 32, 72, 99, 181, 24, 164, 179, 200, 78, 200, 16, 242, 45, 79, 16, 129, 203, 15, 113, 240, 89, 167, 172, 32,
  222, 198, 47, 127, 112, 229, 9, 58, 34, 162, 108, 118, 205, 7, 208, 163, 115, 110, 100, 196, 32, 30, 162, 197, 105, 134, 162, 100, 223,
  60, 1, 241, 218, 80, 227, 137, 188, 208, 105, 93, 217, 183, 205, 121, 8, 111, 194, 213, 53, 155, 143, 208, 107, 164, 116, 121, 112, 101,
  164, 97, 102, 114, 122,
]

export const txAssetXfer = [
  137, 164, 97, 97, 109, 116, 10, 164, 97, 114, 99, 118, 196, 32, 86, 149, 120, 43, 210, 87, 218, 245, 240, 34, 71, 114, 243, 188, 72, 116,
  212, 242, 145, 254, 132, 88, 187, 108, 72, 154, 171, 40, 86, 45, 162, 57, 163, 102, 101, 101, 205, 9, 16, 162, 102, 118, 205, 3, 232, 162,
  103, 104, 196, 32, 72, 99, 181, 24, 164, 179, 200, 78, 200, 16, 242, 45, 79, 16, 129, 203, 15, 113, 240, 89, 167, 172, 32, 222, 198, 47,
  127, 112, 229, 9, 58, 34, 162, 108, 118, 205, 7, 208, 163, 115, 110, 100, 196, 32, 86, 149, 120, 43, 210, 87, 218, 245, 240, 34, 71, 114,
  243, 188, 72, 116, 212, 242, 145, 254, 132, 88, 187, 108, 72, 154, 171, 40, 86, 45, 162, 57, 164, 116, 121, 112, 101, 165, 97, 120, 102,
  101, 114, 164, 120, 97, 105, 100, 205, 4, 210,
]

export const txAssetConfig = [
  136, 164, 97, 112, 97, 114, 132, 161, 99, 196, 32, 84, 107, 24, 45, 17, 156, 227, 15, 99, 178, 55, 184, 156, 217, 164, 104, 232, 43, 180,
  255, 215, 53, 123, 85, 219, 151, 28, 169, 128, 32, 175, 64, 161, 102, 196, 32, 67, 183, 197, 138, 6, 218, 192, 233, 7, 232, 191, 109, 116,
  50, 117, 124, 110, 93, 63, 106, 116, 225, 229, 102, 101, 134, 201, 162, 26, 182, 148, 78, 161, 109, 196, 32, 200, 68, 255, 169, 13, 75,
  248, 157, 166, 164, 74, 28, 140, 190, 109, 45, 90, 126, 101, 160, 50, 164, 128, 177, 27, 113, 63, 34, 214, 27, 173, 58, 161, 114, 196, 32,
  34, 119, 92, 43, 165, 171, 121, 151, 242, 243, 150, 163, 43, 55, 202, 149, 110, 138, 32, 31, 181, 182, 72, 29, 185, 8, 63, 74, 58, 101,
  207, 81, 164, 99, 97, 105, 100, 205, 4, 210, 163, 102, 101, 101, 205, 13, 32, 162, 102, 118, 205, 3, 232, 162, 103, 104, 196, 32, 72, 99,
  181, 24, 164, 179, 200, 78, 200, 16, 242, 45, 79, 16, 129, 203, 15, 113, 240, 89, 167, 172, 32, 222, 198, 47, 127, 112, 229, 9, 58, 34,
  162, 108, 118, 205, 7, 208, 163, 115, 110, 100, 196, 32, 159, 196, 157, 204, 110, 90, 9, 21, 46, 44, 29, 174, 156, 77, 5, 145, 203, 185,
  245, 231, 184, 177, 44, 138, 43, 232, 150, 199, 191, 161, 237, 103, 164, 116, 121, 112, 101, 164, 97, 99, 102, 103,
]

export const txKeyreg = [
  140, 163, 102, 101, 101, 205, 14, 66, 162, 102, 118, 205, 3, 231, 162, 103, 104, 196, 32, 72, 99, 181, 24, 164, 179, 200, 78, 200, 16,
  242, 45, 79, 16, 129, 203, 15, 113, 240, 89, 167, 172, 32, 222, 198, 47, 127, 112, 229, 9, 58, 34, 162, 108, 118, 205, 13, 128, 166, 115,
  101, 108, 107, 101, 121, 196, 32, 119, 30, 245, 236, 189, 238, 56, 130, 27, 254, 58, 253, 56, 140, 165, 179, 89, 121, 18, 45, 52, 52, 88,
  17, 107, 127, 52, 195, 180, 231, 62, 190, 163, 115, 110, 100, 196, 32, 187, 14, 182, 52, 21, 74, 24, 11, 106, 39, 77, 215, 117, 41, 92,
  54, 211, 186, 122, 174, 107, 93, 176, 204, 16, 197, 70, 45, 176, 243, 48, 223, 167, 115, 112, 114, 102, 107, 101, 121, 196, 64, 153, 132,
  116, 25, 81, 14, 108, 196, 210, 53, 219, 10, 51, 164, 112, 99, 44, 7, 96, 250, 149, 14, 168, 55, 19, 130, 69, 207, 22, 78, 173, 225, 253,
  53, 79, 1, 250, 210, 179, 81, 169, 242, 99, 192, 16, 215, 142, 33, 17, 56, 18, 49, 126, 223, 93, 108, 35, 5, 209, 243, 232, 5, 164, 247,
  164, 116, 121, 112, 101, 166, 107, 101, 121, 114, 101, 103, 167, 118, 111, 116, 101, 102, 115, 116, 1, 166, 118, 111, 116, 101, 107, 100,
  10, 167, 118, 111, 116, 101, 107, 101, 121, 196, 32, 246, 106, 245, 221, 24, 188, 172, 87, 169, 196, 221, 224, 132, 133, 43, 100, 219,
  162, 232, 186, 170, 51, 152, 68, 204, 30, 57, 70, 184, 185, 150, 69, 167, 118, 111, 116, 101, 108, 115, 116, 205, 7, 208,
]
export const txKeyreg_offline = [
  134, 163, 102, 101, 101, 205, 7, 8, 162, 102, 118, 205, 3, 231, 162, 103, 104, 196, 32, 72, 99, 181, 24, 164, 179, 200, 78, 200, 16, 242,
  45, 79, 16, 129, 203, 15, 113, 240, 89, 167, 172, 32, 222, 198, 47, 127, 112, 229, 9, 58, 34, 162, 108, 118, 205, 13, 128, 163, 115, 110,
  100, 196, 32, 187, 14, 182, 52, 21, 74, 24, 11, 106, 39, 77, 215, 117, 41, 92, 54, 211, 186, 122, 174, 107, 93, 176, 204, 16, 197, 70, 45,
  176, 243, 48, 223, 164, 116, 121, 112, 101, 166, 107, 101, 121, 114, 101, 103,
]
export const txKeyreg_nonparticipation = [
  135, 163, 102, 101, 101, 205, 7, 98, 162, 102, 118, 205, 3, 231, 162, 103, 104, 196, 32, 72, 99, 181, 24, 164, 179, 200, 78, 200, 16, 242,
  45, 79, 16, 129, 203, 15, 113, 240, 89, 167, 172, 32, 222, 198, 47, 127, 112, 229, 9, 58, 34, 162, 108, 118, 205, 13, 128, 167, 110, 111,
  110, 112, 97, 114, 116, 195, 163, 115, 110, 100, 196, 32, 187, 14, 182, 52, 21, 74, 24, 11, 106, 39, 77, 215, 117, 41, 92, 54, 211, 186,
  122, 174, 107, 93, 176, 204, 16, 197, 70, 45, 176, 243, 48, 223, 164, 116, 121, 112, 101, 166, 107, 101, 121, 114, 101, 103,
]

export const txPayment = [
  139, 163, 97, 109, 116, 205, 3, 232, 165, 99, 108, 111, 115, 101, 196, 32, 64, 233, 52, 146, 136, 37, 100, 203, 206, 156, 89, 166, 155,
  103, 84, 38, 137, 233, 161, 195, 162, 169, 234, 91, 101, 166, 232, 164, 66, 31, 252, 87, 163, 102, 101, 101, 205, 3, 232, 162, 102, 118,
  205, 48, 57, 163, 103, 101, 110, 172, 100, 101, 118, 110, 101, 116, 45, 118, 51, 56, 46, 48, 162, 103, 104, 196, 32, 254, 179, 108, 57,
  16, 20, 57, 0, 195, 218, 85, 66, 202, 24, 54, 176, 15, 210, 248, 25, 89, 18, 87, 205, 35, 246, 4, 47, 152, 200, 54, 157, 162, 108, 118,
  205, 246, 253, 164, 110, 111, 116, 101, 196, 8, 69, 38, 34, 0, 24, 82, 134, 251, 163, 114, 99, 118, 196, 32, 123, 108, 226, 79, 235, 91,
  172, 192, 177, 100, 226, 156, 34, 44, 87, 245, 246, 61, 195, 135, 212, 57, 4, 130, 88, 65, 28, 95, 225, 15, 124, 2, 163, 115, 110, 100,
  196, 32, 141, 146, 180, 137, 144, 1, 115, 160, 77, 250, 67, 89, 163, 102, 106, 106, 252, 234, 44, 66, 160, 93, 217, 193, 247, 62, 235,
  165, 71, 128, 55, 233, 164, 116, 121, 112, 101, 163, 112, 97, 121,
]

export const txApplication = [
  222, 0, 17, 164, 97, 112, 97, 97, 146, 196, 1, 0, 196, 2, 1, 2, 164, 97, 112, 97, 110, 1, 164, 97, 112, 97, 112, 196, 5, 1, 32, 1, 1, 34,
  164, 97, 112, 97, 115, 145, 6, 164, 97, 112, 97, 116, 146, 196, 32, 187, 14, 182, 52, 21, 74, 24, 11, 106, 39, 77, 215, 117, 41, 92, 54,
  211, 186, 122, 174, 107, 93, 176, 204, 16, 197, 70, 45, 176, 243, 48, 223, 196, 32, 160, 137, 170, 105, 34, 227, 185, 152, 250, 223, 246,
  205, 72, 8, 221, 249, 224, 33, 228, 148, 78, 56, 158, 163, 213, 198, 56, 120, 102, 137, 25, 126, 164, 97, 112, 102, 97, 145, 3, 164, 97,
  112, 103, 115, 130, 163, 110, 98, 115, 2, 163, 110, 117, 105, 1, 164, 97, 112, 108, 115, 130, 163, 110, 98, 115, 4, 163, 110, 117, 105, 3,
  164, 97, 112, 115, 117, 196, 5, 2, 32, 1, 1, 34, 163, 102, 101, 101, 205, 3, 232, 162, 102, 118, 206, 0, 4, 236, 15, 163, 103, 101, 110,
  172, 116, 101, 115, 116, 110, 101, 116, 45, 118, 49, 46, 48, 162, 103, 104, 196, 32, 72, 99, 181, 24, 164, 179, 200, 78, 200, 16, 242, 45,
  79, 16, 129, 203, 15, 113, 240, 89, 167, 172, 32, 222, 198, 47, 127, 112, 229, 9, 58, 34, 162, 108, 118, 206, 0, 4, 239, 247, 164, 110,
  111, 116, 101, 196, 10, 110, 111, 116, 101, 32, 118, 97, 108, 117, 101, 163, 115, 110, 100, 196, 32, 9, 251, 210, 118, 44, 8, 248, 108,
  90, 230, 191, 109, 215, 167, 169, 1, 222, 102, 117, 215, 80, 224, 126, 140, 92, 118, 152, 100, 125, 182, 225, 253, 164, 116, 121, 112,
  101, 164, 97, 112, 112, 108,
]

export const txApplicationLong =
  'de0011a46170616198c4fa9fdd8fe9420e5d401d02050d78f5d13ea9f209d0a101e382f70d13d4dced8f5425a96ace5c8858b8654b2a3904cf175b1f9cee6069d765f1fe42fa23151dd9baa382f709a1681267b8ee9f47f7964c0e7e9ab3cf426964433ec29a17150ac82bce2b5044512412d0522586f2d52338584173242117110426cfbf22fb416a298bcdbfc02018dc8689d773f564516bd40eec2831147cc56729d92b743cfa3b585b1bc7c9383735cf5c6459efce18bc773a5014d1f7000011e671f05ad740cc4349e365f700fb73f06dc4da14c46bbb47e1b920d9b2b5c7506bc2e3af13a561f065d54c3ca6333078e803f12b12d6b1e6276b76e8ce5c95a8930607c4fa1a79a6c371f3bdb6ecaef12c98118b51e64cc6190a362a521c4feff89f3ac9b6ea2804e52ee1a09601a3dd4d6da599052238ef69b14da54fac103081ac627d0c9cd6196103e2798427f999c6737ef0e770f8096a97100ed05b5127d1bc686c1d2f634fc87f569792de426e496e6f2d36e586961c1babeca1f9122fdea0be1ac6f3bd89eae5ced97066983c30a41bd946265083aef7cab65394586a0226e9fb9f9caf65ef7e9ac69a711b483e21b60f501aea434af068985547a8065eb1a8db313e83e5551e2535be7cc6f05b48920b2cb2a2d84be39f8cfb3f20ea66adda16bd4396f7703827ad77edab3f1b3953f12e193367e994f9943972afc4fa69f8e9851b4e31fcd4c7980552a273ad0a982685b50e9b2e2481131a4901b5d9ecc8595c6f3d29a6f4f7a9afe5e3466e7edd1bd811050744cf5ea26f36d5e2d82ec4e86a98104da56fd1a20e41e75694f2329d2dc9910cb48dc1927d43926c424c3f012634c7f778fee148372025dccf07af54e01d308a63f5cd0b99eea963a914e1f366bba3fb026e43e6244fa934ce990bb3ba6d8d408e017eb2a7aba1bbb191c5868e044ce2628ec70ee5506efe1f3ae7f326db07438b3ec99b9c64a960078c03f88c77b4ab6a9826c8f7399fdfd80008c9da7622886805bc1b0b9fef2b3a9fddd94b8f7852bc24d2f8d081003a5e7bd54b40df125cf3d639c4fa6bf2401f9bbf4550cf056c47d1b5b18fd11e2f1b6a910650a7bc161b38bf8c18a97de0909ec1d42154f07530fa15f658484e1403f4bbbb836e106837b56977f43ce72e1cf6c8222c5726dc9ab61261c59c0308d0caec0e79f629fea21c4d5e37657d350f2bed1320f4df74f90078c6800779700a1b6f851bd6a4662ee1a2f1965491615cdd484827cfe830fe4e7c482f956431f8cef99614cc367165ddc3e75877ecbca5223c73c8e7a9aadc7a007c7f40a69ae9f97469f08bf2cd1d62f1aea8833b5e063ce743c6a7670e6ad82c802563d217efc9e461b4b503fec0c8c28ab5ee4ab55bcf5789cff1aabed964b7fbe642ad0a4584d31e66d1c9c4fa4badbbfe681e82d4fcc34edcfb176fc16221a9271086bc5933e43ea47be65d75aa3e225b1b223a8376dd7a7751cc0c825b032da8d202f251f19b58a7313ea10bd791d59b942937bfd24d4d7f781cce8c58ba9350fa3adefca37b1fb070c9c4fa6eb7f1cc6ed99a7a98d8d8f00279ca68a1885393131be65d330ca93dd76f99297c48a2ed5c853aefe61a0758aa359d61b9e1aefb1106303a05fc4ba843662be86d97f70b01241dd0693d5f01aa0f2938da6b2c47b0d96042a21470b03fee201a97f4b2070743250c3a640e2647c36920c40c63348c037acdd4d9f6e4b86a7d5cf87f1b1d8ccbf6f7cedcf9cfe9c2105ca300d0e074cf5c5b9c0bc4fae111faa1ce7b4cbd47f528fb5327c3badec3db5698695af695d7c9db8210f924c1220801769ad2b65ea72bd518b46f351a1804b3e93496d1e9834e3546abe76493481992e24fc4573f457e4aea0084cbea1eb91caee15da54452b41858da726e9ac10b4232f107908c9f2b936865a19377890aaad5b2f158d88cc53df26bdf4d51b3a0b1b94d4441de1a0c0a8c517de54538c647290dbb4db054699989f206dbd1299a63b2d5672059cada5134e0cd0478e17989c5ea55f1b298984ba5728f7c79bc84e79083f83853a9f09bbe0560da7e6cfe3c7657578d1994b824eb7c25b4c0803f9768040aa522d4e9fba8531800498bd12785f7d9d28753c4fa388cdf4dee8b9874da3c94bf4cedd8b8b5bd9a5ce3eb407224fc3b19e422c9455e090b6052cedc4d1107d8613578a775b058b91af5b0450836e0d768fad6fdbfcb9686ec326719d86d8ffdd5c91ceb6fe05e0e2fc84f477a43435b2112807b6858a590cc6bbfc22630dee70732bc44b1278ec540a8828575f4d1c1ce5f67d1a3c56adec705b7079441f8263b6a0b6e4cf88196e56ec1ec3e21162d4bc1d5d73552eb5870172932e3ef4899e8ded2f2ee203466afa87a48dbad2c7f90a8924ced012ace8b03fbee69dcc01c61691261da545973c2c41e1f4af7cd2c97c3068f6bd32bb1efcded16cae7c0698269efda034aaae5651eeb3fc58280c4fa9c97c887a9136dbcfb6b496bbe84b32448d8e3e4be62f3db55b702b8e950b351dcd9593297aa1e890e82511caa3aec28c9da8204aca8cb1fbd5389a9de3f653bacf053d8b875ca08080fe7ed5dac2dfc77745416e5a30a51535d473939bd167cc4c687047c44f9fa6bcd6f978b7005a135c6b0b8c0416d9e17ea3ba8a5089089c39151b6a27e1e1fa07fe3c8daabec26c865767882e0e6ef7201f3b4865514843000b6ad84817f2c08916bba9ba5f4195a2c9c6e3b0b80426620f8cd206932a89e6e8e82d4fbb77b9a2c584e02252619d7478768ab43390251a4d7577063516d18fc62c299fe62b0bfc8cd79a133f2a7976132e1ac1d8fcf16f0a46170616e04a461706170c480c0721b691b335da47a695a7246492eb3fb88c3b3463024439091287154a3c409d4f0389bb7d9a9ab49237b671cfe5b293141039e91555f76bab6cd5adedc5489c207e20070c47eb6d7cc12330c4fb4f048f28fe24f1ab69e7a58e29b51753b33146e8c32a3bdc716e5956572281d63c27d7e7b59e1fd5d42feedb568ada19c5ea46170617392cd1b70cd1d4ea46170617494c42033627e03aaa4c34b2e3ae7aa2d049a776afdf3d8beebde452f27e60837febc32c420eb3b7a3800eae990c379c60c3ab0f571225954f7be5190435810332d695ac82ac42044d211e4acc09eb27d59773c62e5e9e8a8fbc76d460bd2c542ea618eb63f03dcc420931468e76ebfb4b466ab82edfb5b0c395f05f7d70c0ea970c8d96b01c43d2841a46170666192cd0137cd079ea46170677382a36e6273ce17c2f571a36e7569ce35326631a461706c7382a36e6273ce039892fca36e7569ce42f762faa461707375c4201be56dfbb007190ed78a890b9a613c0e8b6656bee4e874f53f6d6dae9e54df14a3666565cd03e8a26676ce000dc8cda367656eac746573746e65742d76312e30a26768c4204863b518a4b3c84ec810f22d4f1081cb0f71f059a7ac20dec62f7f70e5093a22a26c76ce0017c94ca46e6f7465c504007475727069732065676573746173207072657469756d2061656e65616e207068617265747261206d61676e6120616320706c61636572617420766573746962756c756d206c6563747573206d617572697320756c7472696365732065726f7320696e2063757273757320747572706973206d617373612074696e636964756e7420647569207574206f726e617265206c65637475732073697420616d65742065737420706c61636572617420696e2065676573746173206572617420696d706572646965742073656420657569736d6f64206e69736920706f727461206c6f72656d206d6f6c6c697320616c697175616d20757420706f72747469746f72206c656f2061206469616d20736f6c6c696369747564696e2074656d706f72206964206575206e69736c206e756e63206d6920697073756d20666175636962757320766974616520616c6971756574206e656320756c6c616d636f727065722073697420616d6574207269737573206e756c6c616d20656765742066656c69732065676574206e756e63206c6f626f72746973206d617474697320616c697175616d20666175636962757320707572757320696e206d617373612074656d706f72206e65632066657567696174206e69736c207072657469756d2066757363652069642076656c697420757420746f72746f72207072657469756d20766976657272612073757370656e646973736520706f74656e7469206e756c6c616d20616320746f72746f72207669746165207075727573206661756369627573206f726e6172652073757370656e646973736520736564206e697369206c616375732073656420746f72746f72207669746165207075727573206661756369627573206f726e6172652073757370656e646973736520736564206e697369206c616375732073656420746f72746f72207669746165207075727573206661756369627573206f726e6172652073757370656e646973736520736564206e697369206c616375732073656420746f72746f72207669746165207075727573206661756369627573206f726e6172652073757370656e646973736520736564206e697369206c616375732073656420746f72746f72207669746165207075727573206661756369627573206f726e6172652073757370656e646973736520736564206e697369206c616375732073656420746f72746f72207669746165207075727573206661756369627573206f726e6172652073757370656e646973736520736564206e697369206c616375732073656420746f72746f72207669746165207075727573206661756369627573206f726e6172652073757370656e646973736520736564206e697369206c616375732073656420746f72746f72207669746165207075727573a3736e64c420626def77f13c1e0ec9ec64d9bc10a4f3111b4986a01dd15e4e11a36af98b3d2da474797065a46170706c'
