# planck-base

Planck **rev6** (OLKB, QMK Proton C / STM32F303, 부트로더 `stm32-dfu`) 용 개인 QMK 키맵 설정.
QMK 소스 전체가 아니라 **키맵 관련 파일만** 담은 저장소 — [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware)를 클론한 뒤 아래 위치에 이 저장소 내용을 넣으면 된다.

```
qmk_firmware/keyboards/planck/keymaps/planckkey/
├── keymap.c
├── rules.mk
└── config.h
```

원본은 QMK Configurator에서 만든 `planck-rev6-planckkey.json`(이 저장소에 같이 포함)이고, `keymap.c`는 그걸 직접 옮긴 뒤 매크로/콤보를 추가한 버전이다. `firmware/planck_rev6_planckkey.bin`은 마지막으로 빌드해서 실제 키보드에 플래시한 결과물 (재빌드하면 갱신됨, 커밋 시점의 스냅샷).

---

## 레이어 구성

| # | 이름 | 켜는 법 |
|---|---|---|
| 0 | `_BASE` | 기본 |
| 1 | `_NUM` | 넘패드 — 왼쪽 Alt 자리 홀드(`LT(1,KC_LALT)`) 또는 오른쪽 끝 `TG(1)`로 토글 |
| 2 | `_FUNC` | F1~F12 — 왼쪽 아래 `MO(2)` 홀드 |
| 3 | `_SYM` | 심볼(`~!@#...`) — `MO(3)` 홀드 |
| 4 | `_NUMSYM` | 숫자/기호(`` ` ``, `[`, `]`, `\`, `-`, `=`) — `MO(4)` 홀드 |
| 5 | `_L5` | *(비어 있음)* — 번호 유지용 placeholder |
| 6 | `_L6` | *(비어 있음)* — `_SYM`/`_NUMSYM`의 `MO(6)`가 가리키는 자리, 아직 내용 없음 |

---

## 레이어별 상세 키맵 (Keymap Tables)

> [!NOTE]
> `▽` (`KC_TRNS`) 표시는 투명 키로, 해당 위치를 누르면 하위 활성 레이어의 키 매핑이 그대로 동작합니다.

### Layer 0: `_BASE` (기본 레이어)

| Row | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 | Col 8 | Col 9 | Col 10 | Col 11 | Col 12 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **0** | `Esc` | `Q` | `W` | `E` | `R` | `T` | `Y` | `U` | `I` | `O` | `P` | `Bksp` |
| **1** | `Tab` | `A` | `S` | `D` | `F` | `G` | `H` | `J` | `K` | `L` | `;` | `Enter` |
| **2** | `Shift` | `Z` *(Undo)* | `X` *(Cut)* | `C` *(Copy)* | `V` *(Paste)* | `B` | `N` | `M` | `,` | `.` | `/` | `RShift` |
| **3** | `Ctrl` | `MO(2)` *(Func)* | `GUI` *(Win/Cmd)* | `LT(1,Alt)` *(Num)* | `MO(4)` *(NumSym)* | `Bksp` | `Space` | `MO(3)` *(Sym)* | `Caps` | `Vol-` | `Vol+` | `TG(1)` *(Num)* |

---

### Layer 1: `_NUM` (넘패드 레이어)

- **진입**: 좌하단 `LT(1, KC_LALT)` 홀드 또는 우하단 `TG(1)` 토글
- 오른손 영역에 텐키패드(7, 8, 9 / 4, 5, 6 / 1, 2, 3 / 0, .) 배치

| Row | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 | Col 8 | Col 9 | Col 10 | Col 11 | Col 12 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **0** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `7` | `8` | `9` | `+` | `▽` |
| **1** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `4` | `5` | `6` | `-` | `▽` |
| **2** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `1` | `2` | `3` | `=` | `▽` |
| **3** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `0` | `.` | `▽` | `▽` |

---

### Layer 2: `_FUNC` (펑션 & 설정 레이어)

- **진입**: 좌하단 `MO(2)` 홀드
- 상단 F1~F12, `Enter` 자리에 `Delete`, `M` 자리에 Windows/Mac 모드 토글(`MACWIN_TOGG`) 배치

| Row | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 | Col 8 | Col 9 | Col 10 | Col 11 | Col 12 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **0** | `F1` | `F2` | `F3` | `F4` | `F5` | `F6` | `F7` | `F8` | `F9` | `F10` | `F11` | `F12` |
| **1** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `Del` |
| **2** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `Mac/Win` | `▽` | `▽` | `▽` | `▽` |
| **3** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` |

---

### Layer 3: `_SYM` (특수 기호 레이어)

- **진입**: 하단 `MO(3)` 홀드
- 숫자열 Shift 특수기호(`~!@#$%^&*()`) 및 괄호/연산자 기호

| Row | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 | Col 8 | Col 9 | Col 10 | Col 11 | Col 12 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **0** | `~` | `!` | `@` | `#` | `$` | `%` | `^` | `&` | `*` | `(` | `)` | `Bksp` |
| **1** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `{` | `}` | `\|` | `"` | `▽` | `▽` |
| **2** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `-` | `+` | `▽` | `▽` | `▽` | `▽` |
| **3** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `MO(6)` | `▽` | `▽` | `▽` | `▽` |

---

### Layer 4: `_NUMSYM` (숫자 및 기호 레이어)

- **진입**: 하단 `MO(4)` 홀드
- 숫자열(`1`~`0`), 그레이브(`` ` ``) 및 대괄호/슬래시 기호

| Row | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 | Col 8 | Col 9 | Col 10 | Col 11 | Col 12 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **0** | `` ` `` | `1` | `2` | `3` | `4` | `5` | `6` | `7` | `8` | `9` | `0` | `▽` |
| **1** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `[` | `]` | `\` | `'` | `▽` | `▽` |
| **2** | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `_` | `=` | `▽` | `▽` | `▽` | `▽` |
| **3** | `▽` | `▽` | `▽` | `▽` | `MO(6)` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` | `▽` |

---

### Layer 5 & 6: `_L5`, `_L6` (예약 / 미사용)

- 모든 키가 `KC_TRNS`(`▽`)로 매핑된 확장용 플레이스홀더 레이어.

---

## Base 레이어에서 원본 대비 바뀐 것

- Z/X/C/V → 탭-홀드 커스텀 키(`CT_UNDO`/`CT_CUT`/`CT_COPY`/`CT_PASTE`, 아래 참고)
- Enter 바로 아래(row2 맨 끝, 원래 `KC_NO`) → `KC_RSFT` (오른쪽 Shift)
- `_FUNC` 레이어의 M 자리(`MO(2)+M`) → `MACWIN_TOGG` (Windows/Mac 모드 토글)
- `_FUNC` 레이어의 Enter 자리(`MO(2)+Enter`) → `KC_DEL` (정방향 삭제 — 원래 키맵 어디에도 Delete가 없어서 추가함)
- `_NUM` 레이어의 `=` 자리: 원래 `KC_PEQL`(넘패드 전용 이퀄)이었는데 `KC_EQL`(일반 이퀄)로 교체 — 아래 버그 기록 참고
- `_NUM` 레이어의 B 자리에 원본에 남아있던 잔여 `KC_V`(넘패드 레이어인데 이 칸만 투명이 아니라 V가 찍혔음) 제거 → `KC_TRNS`

---

## Windows/Mac 모드 (`MACWIN_TOGG`)

- **켜는 법**: `MO(2)`(Func) 홀드 + `M`
- EEPROM에 저장돼서 **전원을 껐다 켜도 유지**된다 (`eeconfig_read_user`/`eeconfig_update_user`).
- 기본값(최초 플래시 시): Windows 모드
- 이 값(`user_config.mac_mode`)이 Z/X/C/V 홀드 동작, J+L 한영전환, Q+W 스크린샷 콤보의 분기 기준이 된다.

## Z/X/C/V — 탭-홀드 (Undo/Cut/Copy/Paste)

- **짧게 탭**: 그냥 z/x/c/v 글자
- **`ZXCV_HOLD_TERM`(200ms) 이상 누르고 있으면**: Windows 모드 → `Ctrl+`글자, Mac 모드 → `Cmd+`글자
- 구현: QMK 내장 `MT()`가 아니라 **직접 짠 탭-홀드 상태 머신** (`process_record_user` + `matrix_scan_user`).
  - `MT()`를 못 쓴 이유: `MT(mod, kc)`의 "홀드"는 모디파이어만 누르고 있는 상태일 뿐, 같은 키(kc) 자체를 다시 보내주지 않는다. 즉 Z를 길게 눌러도 Ctrl만 눌리고 Z는 전송이 안 돼서 Undo가 안 걸린다. "같은 키를 탭+홀드 둘 다에 쓰는" 용도는 QMK 내장 기능으로 안 된다.

---

## 겪었던 버그와 수정 (연속성 기록용)

1. **롤링 타이핑 순서 뒤바뀜** (`ㅋㅏ` → `ㅏㅋ`)
   - 원인: 최초 구현이 "누른 순간 아무것도 안 보내고 떼거나 200ms 지날 때까지 기다렸다가" 보내는 방식이라, 대기 중에 다음 키(K)가 먼저 전송돼버림.
   - 해결: `zxcv_resolve_pending_as_tap()` — 다른 키가 눌리는 순간, 아직 판정 안 된 Z/X/C/V가 있으면 그 키의 인터럽트 처리보다 먼저 즉시 탭으로 확정해서 내보냄. QMK 내장 탭-홀드가 인터럽트 키를 큐에 담아뒀다가 순서대로 재생하는 것과 동일한 효과를 수동으로 낸 것.
2. **잘라내기 후 마우스 클릭이 이상해짐 / 엉뚱한 글자가 한 번 더 찍힘**
   - 원인: 홀드가 확정될 때(`triggered = true`) `pending` 플래그를 안 지워서, 키를 뗀 뒤에도 "아직 대기 중" 상태로 남아있었음. 그 상태에서 Ctrl/Cmd를 물리적으로 키가 눌려있는 내내 `register_code`로 계속 누르고 있었기 때문에, 손을 떼기 전에 마우스를 클릭하면 Ctrl+클릭/Cmd+클릭으로 인식됨. 또 다음 키 입력 때 남아있던 `pending` 때문에 글자가 한 번 더 찍힘.
   - 해결: 홀드가 확정되는 순간 `pending = false`로 같이 정리하고, Ctrl(Cmd)+글자를 **누른 채로 유지하지 않고 한 번의 완결된 탭**(`register_code(mod)` → `tap_code(base)` → `unregister_code(mod)`)으로만 보내도록 변경. 물리 키를 아무리 오래 누르고 있어도 모디파이어가 남아있지 않음.
3. **Windows에서 J+L 한영전환이 안 됨**
   - 원인: 한때 "OS 분기 없이 무조건 Ctrl+Space" 로 만들었는데, macOS는 Ctrl+Space가 기본 입력 소스 전환 단축키라 바로 되지만 **Windows Korean IME는 Ctrl+Space가 기본으로 한/영 전환에 매핑돼 있지 않음** (최신 Windows 11에서는 그 설정 화면 자체를 찾기도 어려움).
   - 해결: 다시 OS별로 분기 — Windows는 진짜 하드웨어 한/영 키에 해당하는 `KC_LNG1`(설정 없이 바로 동작), Mac은 `Ctrl+Space`(맥 기본값) 그대로 유지.
4. **ㅓ(J) 키가 가끔 아예 안 눌림**
   - 처음엔 "J가 콤보(J+L)에 묶여서 최대 50ms 지연되는 것 아니냐"고 의심해서 J+L/Q+W 콤보를 `_FUNC` 레이어 탭 방식(Func+J, Func+Q)으로 옮겼었음.
   - 하지만 같은 콤보의 짝인 L, 그리고 Q/W는 전혀 지연이 없다고 확인됨 → 콤보 이론 기각. 실제 원인은 **핫스왑 소켓 접점 불량**이었고, 스위치를 뽑았다 다시 꽂으니 해결됨. 순수 하드웨어 문제였음.
   - 그래서 Func 레이어로 옮겼던 것은 다시 원래 콤보 방식(J+L, Q+W)으로 되돌림. 콤보 자체는 죄가 없었다.
5. **넘패드 레이어의 `=`가 안 눌림**
   - 원인: `KC_PEQL`(Keypad Equal, HID 0x67)을 썼는데, 이 코드는 Mac 확장 키보드/계산기용으로나 쓰이는 드문 코드라 **Windows가 아예 인식을 안 함**. 반면 같은 레이어의 Keypad 7/8/9, +, -, 0, . 등은 모든 넘패드에 흔한 코드라 Windows에서도 정상 지원됨 — `=`만 예외였던 것.
   - 해결: 일반 `KC_EQL`(메인 키보드의 평범한 `=`)로 교체.

### 검토했지만 채택 안 한 대안

- **레이어 오버레이 방식** (Windows용 `MT(MOD_LCTL,...)`를 base에, Mac용 `MT(MOD_LGUI,...)`를 숨겨진 레이어에 두고 토글로 전환): 순서 문제는 QMK 내장 엔진이 알아서 해결해주지만, 위에서 설명한 "같은 키 홀드로 Ctrl+Z 자체를 못 보낸다"는 한계 때문에 폐기.
- **QMK 네이티브 `KC_UNDO`/`KC_CUT`/`KC_COPY`/`KC_PASTE`** (HID Keyboard-page 0x7A~0x7D, 모디파이어 없이 단일 키로 "되돌리기" 자체를 의미): OS만 신경 쓰면 되니 `mac_mode` 분기가 통째로 필요 없어져서 코드가 단순해지지만, **macOS와 일부 앱(브라우저, 일렉트론, 게임 등)에서 지원이 불안정**해서 채택 안 함. 모든 앱에서 보장되는 진짜 Ctrl/Cmd+글자 조합을 유지하기로 함.

---

## 콤보

| 콤보 | 위치(Base 기준) | 동작 |
|---|---|---|
| J + L | 두벌식 ㅓ/ㅣ 자리 | 한영전환 — Windows: `KC_LNG1`(진짜 한/영 키), Mac 모드: `Ctrl+Space` |
| Q + W | 왼쪽 위 두 키 | 스크린샷 — Windows: `Win+Shift+S`, Mac 모드: `Cmd+Shift+4` |

- `rules.mk`에 `COMBO_ENABLE = yes` 필요 (이미 설정됨).
- Windows 쪽 한영전환은 `KC_LNG1`이라 별도 OS 설정 없이 바로 동작해야 함 (아직 실기 테스트 전 — 확인 필요).
- Mac 쪽은 macOS 기본 단축키가 "다음 입력 소스로 전환 = Ctrl+Space"라서 별도 설정 없이 바로 동작.

---

## 빌드 & 플래시

### 0. 준비 (최초 1회)

```sh
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
git clone https://github.com/mortalist/planck-base.git /tmp/planck-base
mkdir -p keyboards/planck/keymaps/planckkey
cp /tmp/planck-base/{keymap.c,rules.mk,config.h} keyboards/planck/keymaps/planckkey/
```

### 필요 도구 (Homebrew로 설치, 최초 1회)

이 머신엔 기본적으로 QMK 툴체인이 없어서 아래 tap들을 신뢰(trust) 설정하고 설치해야 했음:

```sh
brew tap qmk/qmk
brew trust qmk/qmk

brew tap osx-cross/arm
brew trust osx-cross/arm

brew tap osx-cross/avr
brew trust osx-cross/avr

brew install qmk
```

`arm-none-eabi-gcc@8`, `avr-gcc@8` 등은 keg-only라 기본 PATH에 안 잡힘. 빌드/플래시 전에 매번:

```sh
export PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/avr-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:/opt/homebrew/opt/avr-binutils/bin:$PATH"
```

### 빌드

`qmk_firmware` 루트에서:

```sh
make planck/rev6:planckkey
```

### 플래시

1. 키보드 맨 왼쪽 위 키(Esc)를 누른 채로 USB 연결 → 부트매직으로 DFU 모드 진입 (rev6는 `bootmagic` 활성화돼 있음, 별도 리셋 버튼 불필요).
2. 확인: `dfu-util -l` → `Found DFU: [0483:df11] ... name="@Internal Flash ..."` 뜨면 정상 인식된 것.
3. 플래시:
   ```sh
   make planck/rev6:planckkey:flash
   ```
   중간에 뜨는 `DFU state(10) = dfuERROR, status(10) = Device's firmware is corrupt` 메시지는 DFU 진입 직후 흔한 정상 상태 메시지이고, 자동으로 클리어되고 이어서 진행됨.

### Mac 없이 (폰으로) 플래시하기

키보드만 손에 있고 빌드용 컴퓨터에 물리적으로 접근 못 할 때: 안드로이드(USB-C) 폰이면 WebUSB로 브라우저에서 바로 DFU 플래싱 가능.

1. USB-C↔USB-C 케이블(데이터 전송 되는 것)로 키보드-폰 연결. 이때 키보드 Esc를 누른 채로 연결해서 DFU 진입.
2. 폰에서 Chrome으로 `https://devanlai.github.io/webdfu/dfu-util/` 접속.
3. Connect → 장치 선택 → **alt=0 "Internal Flash"** 인터페이스 선택 → `.bin` 파일 선택 → Download(장치에 쓰기).
4. iPhone은 WebUSB/USB 호스트 미지원이라 이 방법 불가.

---

## TODO / 알려진 제약

- `_L5`, `_L6` 레이어는 아직 완전히 비어 있음 (플레이스홀더).
- `MACWIN_TOGG` 토글에 아무 시각/청각 피드백이 없음 (지금 모드가 Windows인지 Mac인지 키보드만 보고는 알 수 없음). 필요하면 RGB 표시나 오디오 비프 추가 가능 (rev6은 스피커 있음, `AUDIO_ENABLE`).
- `_SYM` 레이어의 `+`가 `KC_PPLS`(넘패드 플러스 코드)로 되어있음 — 작동엔 문제 없지만(이 코드는 Windows에서도 잘 지원됨), 넘패드 밖 심볼 레이어에서 쓰기엔 다소 일관성이 떨어지는 선택. 우선순위 낮은 정리 대상.
- Windows에서 J+L(`KC_LNG1`) 한영전환 실기 테스트 아직 안 됨 — 확인 필요.
