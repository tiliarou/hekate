# hekate - CTCaer mod

![Image of Hekate](https://i.imgur.com/O3REoy5.png)


커스텀 닌텐도 스위치 부트로더, 펌웨어 패치 프로그램 등.


## 부트로더 폴더와 파일

| 폴더/파일            | 설명                                                                  |
| -------------------- | --------------------------------------------------------------------- |
| bootloader           | 메인 폴더                                                             |
|  \|__ bootlogo.bmp   | 커스텀이 켜 있고 logopath가 발견되지 않은 경우 사용. 건너 뛸 수 있음. |
|  \|__ hekate_ipl.ini | 메인 부트로더 구성 및 부트 항목.                                      |
|  \|__ update.bin     | 최신 버전인 경우 부팅 시 로드. 모드칩. 건너 뛸 수 있음.               |
| bootloader/ini/      | 개인용. 'More configs ...' 메뉴. 자동 부팅이 지원.                    |
| bootloader/sys/      | 시스템 모듈                                                           |
|  \|__ libsys_lp0.bso | LP0 (슬립 모드) 모듈. 중요함!!                                        |
| bootloader/payloads/ | 페이로드의 경우. 'Payloads...' 메뉴. 자동 부팅은 ini에 포함시켜야 지원. 모든 CFW 부트로더, 도구, 리눅스 페이로드 지원 |
| bootloader/libtools/ | 차후 예약                                                             |

**참고**: 7.0.0 이상 부팅을 위한 Sept 파일은 sd 카드의 루트에 있는 /sept 폴더에 있습니다.


## 부트로더 구성

부트 로더는 'bootloader/hekate_ipl.ini'(SD 카드에 있는 경우)를 통해 구성할 수 있습니다. 각 ini 섹션은 글로벌 구성을 제어하는 특수 섹션 'config'를 제외하고는 부트 항목을 나타냅니다.


가능한 네 가지 유형의 항목이 있습니다. "**[ ]**": 부팅 항목, "**{ }**": 캡션, "**#**": 코멘트, "*newline*": .ini 코스메틱 뉴라인.


### 부팅 항목이 **config** 일 때 글로벌 구성 키/값:

| 구성 옵션          | 설명                                                       |
| ------------------ | ---------------------------------------------------------- |
| autoboot=0         | 0: 비활성화, #: 자동 부팅 할 부팅 항목 번호                |
| autoboot_list=0    | 0: hekate_ipl.ini에서 `자동부팅` 부트 항목을 읽고, 1: ini 폴더에서 읽습니다 (ini 파일은 ASCII로 정렬). |
| bootwait=3         | 0: 비활성화 (또한 bootlogo를 비활성화. 주입 후 **VOL-**을 누르면 메뉴로 이동), #: **VOL-**이 메뉴에 들어가기를 기다리는 시간. |
| verification=2     | 0: 백업/복원 확인 비활성화, 1: 드문 (블록 기반, 빠르며 신뢰할 수없는 100%), 2: 전체 (sha256 기반, 저속 및 100% 신뢰할 수 있음). |
| autohosoff=1       | 0: 비활성화, 1: HOS에서 RTC 경보를 통해 깨어난 경우 로고가 표시되고 완전히 꺼짐, 2: 로고가 없으면 즉시 전원 꺼짐.|
| autonogc=1         | 0: 비활성화, 1: 불소성 퓨즈가 발견되고 >= 4.0.0 HOS가 부팅되면 nogc 패치가 자동으로 적용. |
| backlight=100      | 화면 백라이트 수준. 0-255.                                 |


### 가능한 부팅 항목 키/값 조합:

| 구성 옵션          | 설명                                                       |
| ------------------ | ---------------------------------------------------------- |
| logopath={SD 경로} | global customlogo가 1이고 logopath가 비어 있으면 bootlogo.bmp 사용. logopath가 있으면 지정된 비트 맵 로드 |
| warmboot={SD 경로} | warmboot 바이너리 대체                                     |
| secmon={SD 경로}   | 보안 모니터 바이너리 대체                                  |
| kernel={SD 경로}   | 커널 바이너리를 대체                                       |
| kip1={SD 경로}     | 커널 초기 프로세스 대체/추가. 다중을 설정할 수 있음.       |
| kip1={SD 폴더}/*   | .kip/.kip1을 폴더 안에 로드. 단일 kip1 키와 호환           |
| fss0={SD 경로}     | fusee-secondary 바이너리를 가져와 필요한 모든 부분을 추출  |
| kip1patch=패치이름 | kip1 패치 사용. 여러 라인 및/또는 CSV로 지정. 현재 사용 가능한 패치 nosigchk 및 nocmac (처음으로 다운그레이드 할 때 필수) |
| fullsvcperm=1      | SVC 검증을 비활성화 (전체 서비스 권한)                     |
| debugmode=1        | 디버그 모드 활성화. exosphere를 secmon으로 사용하면 더 이상 사용되지 않음 |
| atmosphere=1       | Atmosphère 패치 활성화                                     |
| stock=1            | 스톡 또는 세미-스톡 실행할 때 불필요한 커널 패치 비활성화  |
| payload={SD 경로}  | 페이로드 실행. 도구, 리눅스, CFW 부트 로더 등              |

**참고**: 와일드 카드 (`/*`)를 `kip1`과 함께 사용할 때, 당신은 여전히 그 다음에 정상적인 `kip1`을 사용하여 여분의 단일 kip을 적재할 수 있습니다.

**참고2**: FSS0을 사용하면 exosphere, warmboot 및 모든 코어 kip을 파싱합니다. `fss0`을 정의한 후 `secmon`/`warmboot`를 사용하여 처음 2 번을 오버라이드 할 수 있습니다.
`kip1`을 정의하여 와일드 카드 (`/*`) 사용법을 통해 여분의 kip 또는 많은 kip을 로드할 수 있습니다.

**경고**: `fss0`을 사용할 때 코어 kip을 정의하지 말고 (`/*`를 사용할 때) 폴더에 반드시 포함 시키십시오.


### 페이로드 저장소:

Hekate는 이제 BPMP 환경 외부에서 구성할 수 있는 새로운 저장소를 이진 파일에 포함합니다:

| 오프셋 / 이름        | 설명                                                              |
| -------------------- | ----------------------------------------------------------------- |
| '0x94' boot_cfg      | bit0: 강제 자동부팅, bit1: 실행 로그 표시, bit2: sept 실행.       |
| '0x95' autoboot      | `강제 자동부팅`: 0: 강제 메뉴 이동, 그렇지 않으면 해당 항목 부팅  |
| '0x96' autoboot_list | `강제 자동부팅` 과 `자동부팅` 이 있으면 ini 폴더에서 부팅.        |
| '0x97' extra_cfg     | 예약.                                                             |
| '0x98' rsvd[128]     | 예약.                                                             |


[여기서](./res/hekate_ipl_template.ini) 템플릿을 찾을 수 있습니다.

메인 .ini 파일을 찾을 수 없으면 첫 번째 hekate 부팅시 만들어집니다.


```
hekate     (C) 2018 naehrwert, st4rk
CTCaer mod (C) 2018 CTCaer.

감사한 분들: derrek, nedwill, plutoo, shuffle2, smea, thexyz, yellows8.
인사: fincs, hexkyz, SciresM, Shiny Quagsire, WinterMute.

사용된 오픈 소스 및 무료 패키지:
 - FatFs R0.13a, Copyright (C) 2017, ChaN
 - bcl-1.2.0, Copyright (C) 2003-2006, Marcus Geelnard
 - Atmosphère (SE sha256, prc id kernel patches), Copyright (C) 2018, Atmosphère-NX
 - elfload, Copyright (C) 2014 Owen Shepherd, Copyright (C) 2018 M4xw

                         ___
                      .-'   `'.
                     /         \
                     |         ;
                     |         |           ___.--,
            _.._     |0) = (0) |    _.---'`__.-( (_.
     __.--'`_.. '.__.\    '--. \_.-' ,.--'`     `""`
    ( ,.--'`   ',__ /./;   ;, '.__.'`    __
    _`) )  .---.__.' / |   |\   \__..--""  """--.,_
   `---' .'.''-._.-'`_./  /\ '.  \ _.--''````'''--._`-.__.'
         | |  .' _.-' |  |  \  \  '.               `----`
          \ \/ .'     \  \   '. '-._)
           \/ /        \  \    `=.__`'-.
           / /\         `) )    / / `"".`\
     , _.-'.'\ \        / /    ( (     / /
      `--'`   ) )    .-'.'      '.'.  | (
             (/`    ( (`          ) )  '-;   [switchbrew]
```
