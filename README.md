# Word War - Simple Console Game / コンソールゲーム「Word War」

## 📌 Overview / 概要

**Word War** is a lightweight C++ console game that showcases:
- Basic game loop structure
- Cleanly separated managers (Player, Enemy, Bullet, HealthPack)
- Reusable interfaces (IPlayerSystem, IBulletSystem, etc.)
- Config-driven parameters (JSON)
- Simple collision detection system
- Toggleable debug information

**Word War** は、軽量C++コンソールゲームです：
- 基本的なゲームループ構造
- プレイヤー・敵・弾・回復アイテムのマネージャーを分離
- 再利用可能なインターフェース設計
- JSONで外部設定可能なパラメータ
- シンプルな衝突判定システム
- デバッグ情報のON/OFF機能

---

## 🎮 How to Play / 遊び方

- Use `W A S D` keys to move the player.
  - `W` : Up
  - `A` : Left
  - `S` : Down
  - `D` : Right
- Player fires bullets automatically at intervals.
- Defeat enemies to level up.
- Pick up `[+]` health packs to recover HP.
- Press `0` during gameplay to toggle debug info.
##
- プレイヤーは `W A S D` で移動できます
  - `W` : 上
  - `A` : 左
  - `S` : 下
  - `D` : 右
- プレイヤーは自動で弾を発射
- 敵を倒すとレベルアップ
- `[+]`を取るとHP回復
- ゲーム中に `0` を押すとデバッグ情報を切り替え

---

## ⚙️ Features / 特徴

- **Object-Oriented Design:** Core entities like Player, Enemy, Bullet, and HealthPack inherit from a unified `CharacterBase`.
- **Modular code:** Clean manager & system separation.
- **Interface-driven:** Easy to extend or replace components.
- **Config file:** Adjust speed, spawn rates, symbols easily.
- **Simple UI:** Clear console rendering & side info panel.
- **Debug toggle:** Check runtime stats on the fly.
##
- **オブジェクト指向設計:** Player, Enemy, Bullet, HealthPack を共通の `CharacterBase` から継承
- **モジュール構造:** マネージャー＆システムを分離
- **インターフェース駆動:** 拡張・差し替えが簡単
- **設定ファイル:** 速度やスポーン間隔をJSONで調整
- **シンプルUI:** コンソール表示＆右側パネルで情報表示
- **デバッグ切替:** 実行中に統計を確認可能

---

## 📂 Project Structure / プロジェクト構造
- WordWar/
  - ├── Characters/
  - ├── Items/
  - ├── Managers/
  - ├── Interface/
  - ├── System/
  - ├── Settings/config.json
  - ├── GameMain.cpp / GameMain.h
