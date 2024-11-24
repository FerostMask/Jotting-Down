# 如何书写提示词

> 参考：[20分钟搞懂Prompt与参数设置，你的AI绘画“咒语”学明白了吗？ | 零基础入门Stable Diffusion·保姆级新手教程 | Prompt关键词教学](https://www.bilibili.com/video/BV12X4y1r7QB/?spm_id_from=333.788&vd_source=ddf1780995cb6c48dbcdcc4caa63f28a)

## 内容型提示词

### 任务及主体特征

| 类型     | 提示词                 |
| -------- | ---------------------- |
| 服饰穿搭 | white dress            |
| 发型发色 | blonde hair, long hair |
| 五官特点 | small eyes, big mouth  |
| 面部表情 | smiling                |
| 肢体动作 | stretching arms        |

### 场景特征

| 类型       | 提示词                   |
| ---------- | ------------------------ |
| 室内、室外 | indoor/outdoor           |
| 大场景     | forest, city, street     |
| 小细节     | tree, bush, white flower |

### 环境光照

| 类型     | 提示词                 |
| -------- | ---------------------- |
| 白天黑夜 | day/night              |
| 特定时段 | morning, sunset        |
| 光环境   | sunlight, bright, dark |
| 天空     | blue sky, starry sky   |

### 画幅视角

| 类型     | 提示词                   |
| -------- | ------------------------ |
| 距离     | close-up, distant        |
| 人物比例 | full body, upper body    |
| 观察视角 | from above, view of back |
| 镜头类型 | wide angle, Sony A7 III  |

## 标准化提示词

### 画质提示词

| 类型             | 提示词                                                       |
| ---------------- | ------------------------------------------------------------ |
| 通用高画质       | best quality, ultra-detailed, masterpiece, hires, 8k         |
| 特定高分辨率类型 | extremely detailed CG unity 8k wallpaper, unreal engine rendered |



## 负面提示词

### 实验

```text

(worst quality, low quality:1.4), 

artist name, signature, text, username, watermark, 

error, ugly, duplicate, morbid, mutilated, blurry, deformed, 

bad anatomy, bad proportions, mutation, disfigured,

extra fingers, mutated hands, poorly drawn hands, poorly drawn face, extra limbs, cloned face, malformed limbs, missing arms, missing legs, extra arms, extra legs, fused fingers, too many fingers, long neck, 

embedding:EasyNegativeV2, 
```

