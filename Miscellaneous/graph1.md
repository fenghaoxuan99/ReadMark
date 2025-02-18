<!--
 * @Author: feng 1804831168@qq.com
 * @Date: 2025-02-17 16:39:33
 * @LastEditors: feng 1804831168@qq.com
 * @LastEditTime: 2025-02-17 20:44:57
 * @Description:
 * Copyright (c) 2025 by Feng, All Rights Reserved.
-->

```mermaid
graph RL
    A[数据输入] --> B[知识建模]
    B --> C[推理生成]
    C --> D[动态优化]
    D --> E[质量验证]
    E --> F[知识更新]
    F --> B

    subgraph 知识建模
        B1[海量文献训练] -->|DeBERTa-v3适配预训练| B2[医学语义理解]
        B3[专家标注样本] -->|GAT图注意力网络| B4[决策路径建模]
        B2 -->|SNOMED CT术语库| B5[医学本体构建]
        B5 -->|Neo4j知识图谱| B4
    end

    subgraph 推理生成
        C1[多模态融合] -->|图计算引擎| C2[诊断逻辑链生成]
        C2 -->|Drools规则引擎| C3[临床逻辑校验]
    end

    subgraph 动态优化
        D1[三重约束机制] --> D11[Meta分析证据分级]
        D1 --> D12[语义对齐引擎]
        D1 --> D13[规则冲突检测]
        D3[PPO强化学习] -->|Shapley值反馈| D4[参数矩阵更新]
    end

    subgraph 质量验证
        E1[临床专家委员会] --> E2[循证符合性审查]
        E3[自动化校验引擎] --> E4[本体映射检测]
        E5[动态证据矩阵] --> E6[RCT/观察性研究分级]
    end

    subgraph 知识更新
        F1[Sentence-BERT对齐] -->|指南变更同步| F2[诊断规则库]
        F3[异常决策案例] -->|双闭环反馈| F4[强化学习样本]
    end

    style B2 fill:#cff,stroke:#333
    style B4 fill:#cff,stroke:#333
    style C2 fill:#9f9,stroke:#333
    style D1 fill:#ff9,stroke:#333
    style D3 fill:#f99,stroke:#333
    style E2 fill:#cff,stroke:#333
    style F1 fill:#9f9,stroke:#333

```
