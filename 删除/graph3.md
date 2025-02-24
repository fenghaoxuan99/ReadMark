<!--
 * @Author: feng 1804831168@qq.com
 * @Date: 2025-02-19 13:37:59
 * @LastEditors: feng 1804831168@qq.com
 * @LastEditTime: 2025-02-19 13:38:15
 * @Description: 
 * Copyright (c) 2025 by Feng, All Rights Reserved. 
-->
```mermaid
flowchart TD
    subgraph 领域语义适配流程
        direction TB

        语料库构建 --> 模型架构
        模型架构 --> 预训练任务
        预训练任务 --> 损失函数优化
        损失函数优化 --> 特征向量输出

        subgraph 语料库构建[PubMed语料库]
            direction LR
            A[结构化文献] -->|基础研究| B[疾病机制]
            A -->|临床指南| C[诊疗规范]
            D[术语标准化] --> E[SNOMED CT映射]
        end

        subgraph 模型架构[DeBERTa-v3架构]
            direction TB
            F[解耦注意力机制] --> G[内容-位置分离编码]
            H[相对位置嵌入] --> I[跨段落关联]
            J[增强掩码解码器] --> K[绝对位置补偿]
        end

        subgraph 预训练任务
            direction LR
            L[双向Transformer] --> M[术语上下文建模]
            N[疾病命名实体识别] --> O[F1=0.92]
            P[病理机制解析] --> Q[BLANC=0.85]
        end

  

        特征向量输出 -->|节点初始化| Z[知识图谱]
    end
```
