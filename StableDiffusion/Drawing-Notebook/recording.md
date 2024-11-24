# 泡影 - EtherBluMix7

![ComfyUI_00089_](raws/ComfyUI_00089_.png)

## 提示词

### 正面提示词

```text
1girl,solo,cowboy shot,black hair,portrait,underwater,bubble,blue eyes,air bubble,short hair,blue hair,parted lips,blue theme,looking up,blurry,water,bangs,multicolored hair,floating hair,eyelashes,jewelry,
```

> 翻译：女孩，独奏，牛仔拍，黑发，肖像，水下，泡泡，蓝眼睛，气泡，短发，蓝头发，分唇，蓝色主题，向上看，模糊，水，刘海，多色头发，浮发，睫毛，珠宝，

### 反面提示词

```text
(worst quality, low quality:1.3)
```

> 翻译：(最差质量，低质量:1.3)

## 模型

### CheckPoint

- [EtherBluMix7](https://civitai.com/models/17427?modelVersionId=361779) - 内置vae

### LoRA

- [Vivid Impactful Style](https://civitai.com/models/21722/vivid-impactful-style-yoneyama-mai-style-likeness-loralocon) - 权重：0.7

- [Xian-T手部修复lora](https://www.liblib.ai/modelinfo/855ea21b14ad4c04810eade3f05b0fdd) - 权重：0.6

- [Add More Details](https://civitai.com/models/82098/add-more-details-detail-enhancer-tweaker-lora) - 权重：0.3
- [Oil painting(oil brush stroke) - 油画笔触](https://civitai.com/models/84542/oil-paintingoil-brush-stroke)

## 采样参数

### 初步采样

| 参数           | 数值              |
| -------------- | ----------------- |
| 图片尺寸       | 544x720           |
| 采样方法       | dpmpp_2m - karras |
| 迭代步数       | 60                |
| 提示词引导系数 | 9.0               |
| 去噪           | 1.0               |
| 随机种子       | 300654121553905   |

### 上采样

| 参数           | 数值               |
| -------------- | ------------------ |
| 图片尺寸       | 1080x1440          |
| 采样方法       | dpmpp_sde - karras |
| 迭代步数       | 26                 |
| 提示词引导系数 | 7.5                |
| 去噪           | 0.4                |
| 随机种子       | 726720955306856    |