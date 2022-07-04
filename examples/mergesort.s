	.text
	.file	"comp"
	.globl	get_time                        # -- Begin function get_time
	.p2align	4, 0x90
	.type	get_time,@function
get_time:                               # @get_time
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	leaq	8(%rsp), %rdi
	xorl	%esi, %esi
	callq	gettimeofday@PLT
	movl	16(%rsp), %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	get_time, .Lfunc_end0-get_time
	.cfi_endproc
                                        # -- End function
	.globl	__check_bounds__                # -- Begin function __check_bounds__
	.p2align	4, 0x90
	.type	__check_bounds__,@function
__check_bounds__:                       # @__check_bounds__
	.cfi_startproc
# %bb.0:                                # %entry
	cmpl	%esi, %edi
	jl	.LBB1_2
# %bb.1:                                # %memory_err
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	__unnamed_1@GOTPCREL(%rip), %rdi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	$1, %edi
	callq	exit@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
.LBB1_2:                                # %memory_ok
	retq
.Lfunc_end1:
	.size	__check_bounds__, .Lfunc_end1-__check_bounds__
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$4152, %rsp                     # imm = 0x1038
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movabsq	$13640816134016, %rax           # imm = 0xC6800000780
	movq	%rax, -4184(%rbp)
	movabsq	$9448928054119, %rax            # imm = 0x89800000B67
	movq	%rax, -4176(%rbp)
	movabsq	$8766028255136, %rax            # imm = 0x7F900000FA0
	movq	%rax, -4168(%rbp)
	movabsq	$481036339217, %rax             # imm = 0x7000000811
	movq	%rax, -4160(%rbp)
	movabsq	$12794707578269, %rax           # imm = 0xBA300000D9D
	movq	%rax, -4152(%rbp)
	movabsq	$15337328214732, %rax           # imm = 0xDF3000002CC
	movq	%rax, -4144(%rbp)
	movabsq	$8525510085035, %rax            # imm = 0x7C1000009AB
	movq	%rax, -4136(%rbp)
	movabsq	$15131169788608, %rax           # imm = 0xDC3000012C0
	movq	%rax, -4128(%rbp)
	movabsq	$9779640534328, %rax            # imm = 0x8E500000538
	movq	%rax, -4120(%rbp)
	movabsq	$4239132723654, %rax            # imm = 0x3DB000009C6
	movq	%rax, -4112(%rbp)
	movabsq	$18704582575487, %rax           # imm = 0x11030000057F
	movq	%rax, -4104(%rbp)
	movabsq	$2379411883102, %rax            # imm = 0x22A0000045E
	movq	%rax, -4096(%rbp)
	movabsq	$19696720022272, %rax           # imm = 0x11EA00000B00
	movq	%rax, -4088(%rbp)
	movabsq	$1434519081180, %rax            # imm = 0x14E000010DC
	movq	%rax, -4080(%rbp)
	movabsq	$16458314681008, %rax           # imm = 0xEF800000AB0
	movq	%rax, -4072(%rbp)
	movabsq	$399431961310, %rax             # imm = 0x5D00000ADE
	movq	%rax, -4064(%rbp)
	movabsq	$10471130268961, %rax           # imm = 0x98600000521
	movq	%rax, -4056(%rbp)
	movabsq	$18257905976113, %rax           # imm = 0x109B00000331
	movq	%rax, -4048(%rbp)
	movabsq	$15930033704197, %rax           # imm = 0xE7D00000D05
	movq	%rax, -4040(%rbp)
	movabsq	$9556302235605, %rax            # imm = 0x8B1000007D5
	movq	%rax, -4032(%rbp)
	movabsq	$11574936865318, %rax           # imm = 0xA8700000A26
	movq	%rax, -4024(%rbp)
	movabsq	$18953690679005, %rax           # imm = 0x113D000006DD
	movq	%rax, -4016(%rbp)
	movabsq	$11175504904756, %rax           # imm = 0xA2A00000234
	movq	%rax, -4008(%rbp)
	movabsq	$8727373548294, %rax            # imm = 0x7F000000B06
	movq	%rax, -4000(%rbp)
	movabsq	$4561255269949, %rax            # imm = 0x4260000063D
	movq	%rax, -3992(%rbp)
	movabsq	$18494129181243, %rax           # imm = 0x10D20000123B
	movq	%rax, -3984(%rbp)
	movabsq	$18399639897859, %rax           # imm = 0x10BC00000703
	movq	%rax, -3976(%rbp)
	movabsq	$9947144259124, %rax            # imm = 0x90C00000634
	movq	%rax, -3968(%rbp)
	movabsq	$9650791516650, %rax            # imm = 0x8C7000009EA
	movq	%rax, -3960(%rbp)
	movabsq	$7026566500578, %rax            # imm = 0x664000010E2
	movq	%rax, -3952(%rbp)
	movabsq	$12257836665077, %rax           # imm = 0xB26000008F5
	movq	%rax, -3944(%rbp)
	movabsq	$5265629907361, %rax            # imm = 0x4CA000009A1
	movq	%rax, -3936(%rbp)
	movabsq	$2284922603286, %rax            # imm = 0x21400000716
	movq	%rax, -3928(%rbp)
	movabsq	$4870492914380, %rax            # imm = 0x46E000002CC
	movq	%rax, -3920(%rbp)
	movabsq	$18197776434924, %rax           # imm = 0x108D000006EC
	movq	%rax, -3912(%rbp)
	movabsq	$17609365916279, %rax           # imm = 0x100400000A77
	movq	%rax, -3904(%rbp)
	movabsq	$77309413030, %rax              # imm = 0x12000006A6
	movq	%rax, -3896(%rbp)
	movabsq	$21307332755544, %rax           # imm = 0x136100000058
	movq	%rax, -3888(%rbp)
	movabsq	$16376710302437, %rax           # imm = 0xEE500000AE5
	movq	%rax, -3880(%rbp)
	movabsq	$2568390445333, %rax            # imm = 0x25600000915
	movq	%rax, -3872(%rbp)
	movabsq	$5029406704098, %rax            # imm = 0x493000001E2
	movq	%rax, -3864(%rbp)
	movabsq	$15564961485007, %rax           # imm = 0xE28000010CF
	movq	%rax, -3856(%rbp)
	movabsq	$8688718840684, %rax            # imm = 0x7E70000036C
	movq	%rax, -3848(%rbp)
	movabsq	$12734578035471, %rax           # imm = 0xB9500000B0F
	movq	%rax, -3840(%rbp)
	movabsq	$4969277162230, %rax            # imm = 0x485000002F6
	movq	%rax, -3832(%rbp)
	movabsq	$11416023073591, %rax           # imm = 0xA6200000337
	movq	%rax, -3824(%rbp)
	movabsq	$21118354195446, %rax           # imm = 0x1335000003F6
	movq	%rax, -3816(%rbp)
	movabsq	$19327352832972, %rax           # imm = 0x1194000003CC
	movq	%rax, -3808(%rbp)
	movabsq	$1236950581526, %rax            # imm = 0x12000000116
	movq	%rax, -3800(%rbp)
	movabsq	$16531329126222, %rax           # imm = 0xF0900000F4E
	movq	%rax, -3792(%rbp)
	movabsq	$15028090571211, %rax           # imm = 0xDAB000009CB
	movq	%rax, -3784(%rbp)
	movabsq	$4780298600915, %rax            # imm = 0x459000001D3
	movq	%rax, -3776(%rbp)
	movabsq	$8615704398428, %rax            # imm = 0x7D600000A5C
	movq	%rax, -3768(%rbp)
	movabsq	$18975165518434, %rax           # imm = 0x114200001262
	movq	%rax, -3760(%rbp)
	movabsq	$19258633358087, %rax           # imm = 0x118400000B07
	movq	%rax, -3752(%rbp)
	movabsq	$16299400889112, %rax           # imm = 0xED300000318
	movq	%rax, -3744(%rbp)
	movabsq	$10222022169004, %rax           # imm = 0x94C000011AC
	movq	%rax, -3736(%rbp)
	movabsq	$20508468840146, %rax           # imm = 0x12A7000006D2
	movq	%rax, -3728(%rbp)
	movabsq	$15569256452899, %rax           # imm = 0xE2900001323
	movq	%rax, -3720(%rbp)
	movabsq	$14856291878155, %rax           # imm = 0xD830000050B
	movq	%rax, -3712(%rbp)
	movabsq	$19975892897779, %rax           # imm = 0x122B00000FF3
	movq	%rax, -3704(%rbp)
	movabsq	$9204114918098, %rax            # imm = 0x85F00000AD2
	movq	%rax, -3696(%rbp)
	movabsq	$1795296334074, %rax            # imm = 0x1A2000010FA
	movq	%rax, -3688(%rbp)
	movabsq	$6700148982061, %rax            # imm = 0x6180000012D
	movq	%rax, -3680(%rbp)
	movabsq	$20461224202950, %rax           # imm = 0x129C000012C6
	movq	%rax, -3672(%rbp)
	movabsq	$4853313046188, %rax            # imm = 0x46A000006AC
	movq	%rax, -3664(%rbp)
	movabsq	$9616431779104, %rax            # imm = 0x8BF00000D20
	movq	%rax, -3656(%rbp)
	movabsq	$7975754270358, %rax            # imm = 0x74100000696
	movq	%rax, -3648(%rbp)
	movabsq	$7636451852940, %rax            # imm = 0x6F20000028C
	movq	%rax, -3640(%rbp)
	movabsq	$11544872095926, %rax           # imm = 0xA80000010B6
	movq	%rax, -3632(%rbp)
	movabsq	$16849156703934, %rax           # imm = 0xF53000006BE
	movq	%rax, -3624(%rbp)
	movabsq	$10823317589638, %rax           # imm = 0x9D800000E86
	movq	%rax, -3616(%rbp)
	movabsq	$18575733558319, %rax           # imm = 0x10E500000C2F
	movq	%rax, -3608(%rbp)
	movabsq	$14212046783329, %rax           # imm = 0xCED00000361
	movq	%rax, -3600(%rbp)
	movabsq	$19722489825886, %rax           # imm = 0x11F000000A5E
	movq	%rax, -3592(%rbp)
	movabsq	$19752554597052, %rax           # imm = 0x11F700000ABC
	movq	%rax, -3584(%rbp)
	movabsq	$2302102475483, %rax            # imm = 0x218000012DB
	movq	%rax, -3576(%rbp)
	movabsq	$3435973837027, %rax            # imm = 0x320000000E3
	movq	%rax, -3568(%rbp)
	movabsq	$17811229379808, %rax           # imm = 0x103300000CE0
	movq	%rax, -3560(%rbp)
	movabsq	$13821204759784, %rax           # imm = 0xC92000004E8
	movq	%rax, -3552(%rbp)
	movabsq	$16385300238812, %rax           # imm = 0xEE7000011DC
	movq	%rax, -3544(%rbp)
	movabsq	$11815455036238, %rax           # imm = 0xABF0000134E
	movq	%rax, -3536(%rbp)
	movabsq	$14212046786954, %rax           # imm = 0xCED0000118A
	movq	%rax, -3528(%rbp)
	movabsq	$6648609374928, %rax            # imm = 0x60C000002D0
	movq	%rax, -3520(%rbp)
	movabsq	$6786048331249, %rax            # imm = 0x62C00000DF1
	movq	%rax, -3512(%rbp)
	movabsq	$12107512807748, %rax           # imm = 0xB0300000144
	movq	%rax, -3504(%rbp)
	movabsq	$2070174238907, %rax            # imm = 0x1E2000008BB
	movq	%rax, -3496(%rbp)
	movabsq	$6073083757304, %rax            # imm = 0x586000002F8
	movq	%rax, -3488(%rbp)
	movabsq	$1069446859075, %rax            # imm = 0xF900000943
	movq	%rax, -3480(%rbp)
	movabsq	$19262928325338, %rax           # imm = 0x118500000ADA
	movq	%rax, -3472(%rbp)
	movabsq	$17922898530590, %rax           # imm = 0x104D0000111E
	movq	%rax, -3464(%rbp)
	movabsq	$4793183506635, %rax            # imm = 0x45C000010CB
	movq	%rax, -3456(%rbp)
	movabsq	$1717986923035, %rax            # imm = 0x1900000121B
	movq	%rax, -3448(%rbp)
	movabsq	$18829136627310, %rax           # imm = 0x11200000066E
	movq	%rax, -3440(%rbp)
	movabsq	$1872605743002, %rax            # imm = 0x1B40000079A
	movq	%rax, -3432(%rbp)
	movabsq	$536870913513, %rax             # imm = 0x7D000005E9
	movq	%rax, -3424(%rbp)
	movabsq	$12863427054894, %rax           # imm = 0xBB300000D2E
	movq	%rax, -3416(%rbp)
	movabsq	$2572685412407, %rax            # imm = 0x25700000837
	movq	%rax, -3408(%rbp)
	movabsq	$1421634179283, %rax            # imm = 0x14B000010D3
	movq	%rax, -3400(%rbp)
	movabsq	$15277198673107, %rax           # imm = 0xDE5000004D3
	movq	%rax, -3392(%rbp)
	movabsq	$19713899893496, %rax           # imm = 0x11EE000012F8
	movq	%rax, -3384(%rbp)
	movabsq	$6768868461902, %rax            # imm = 0x62800000D4E
	movq	%rax, -3376(%rbp)
	movabsq	$2044404435524, %rax            # imm = 0x1DC00000A44
	movq	%rax, -3368(%rbp)
	movabsq	$6485400619707, %rax            # imm = 0x5E600000ABB
	movq	%rax, -3360(%rbp)
	movabsq	$10101763080600, %rax           # imm = 0x93000000198
	movq	%rax, -3352(%rbp)
	movabsq	$21449066678675, %rax           # imm = 0x138200000993
	movq	%rax, -3344(%rbp)
	movabsq	$1215475746156, %rax            # imm = 0x11B0000056C
	movq	%rax, -3336(%rbp)
	movabsq	$2310692406607, %rax            # imm = 0x21A0000054F
	movq	%rax, -3328(%rbp)
	movabsq	$5566277619034, %rax            # imm = 0x51000000D5A
	movq	%rax, -3320(%rbp)
	movabsq	$2095944045397, %rax            # imm = 0x1E800001355
	movq	%rax, -3312(%rbp)
	movabsq	$9994388900411, %rax            # imm = 0x91700000A3B
	movq	%rax, -3304(%rbp)
	movabsq	$9633611645645, %rax            # imm = 0x8C3000002CD
	movq	%rax, -3296(%rbp)
	movabsq	$9238474655639, %rax            # imm = 0x86700000797
	movq	%rax, -3288(%rbp)
	movabsq	$9998683868066, %rax            # imm = 0x91800000BA2
	movq	%rax, -3280(%rbp)
	movabsq	$20590073218633, %rax           # imm = 0x12BA00000649
	movq	%rax, -3272(%rbp)
	movabsq	$6764573493672, %rax            # imm = 0x627000009A8
	movq	%rax, -3264(%rbp)
	movabsq	$4221952853309, %rax            # imm = 0x3D70000053D
	movq	%rax, -3256(%rbp)
	movabsq	$19988777799568, %rax           # imm = 0x122E00000F90
	movq	%rax, -3248(%rbp)
	movabsq	$5716601472643, %rax            # imm = 0x53300000683
	movq	%rax, -3240(%rbp)
	movabsq	$20345260085658, %rax           # imm = 0x12810000119A
	movq	%rax, -3232(%rbp)
	movabsq	$16157666970931, %rax           # imm = 0xEB200000D33
	movq	%rax, -3224(%rbp)
	movabsq	$5896990097994, %rax            # imm = 0x55D0000024A
	movq	%rax, -3216(%rbp)
	movabsq	$9977209029673, %rax            # imm = 0x91300000429
	movq	%rax, -3208(%rbp)
	movabsq	$7391638717404, %rax            # imm = 0x6B9000003DC
	movq	%rax, -3200(%rbp)
	movabsq	$8929237008390, %rax            # imm = 0x81F00000006
	movq	%rax, -3192(%rbp)
	movabsq	$14074607830632, %rax           # imm = 0xCCD00000668
	movq	%rax, -3184(%rbp)
	movabsq	$13176959667269, %rax           # imm = 0xBFC00000C45
	movq	%rax, -3176(%rbp)
	movabsq	$9594956940504, %rax            # imm = 0x8BA000004D8
	movq	%rax, -3168(%rbp)
	movabsq	$9994388900717, %rax            # imm = 0x91700000B6D
	movq	%rax, -3160(%rbp)
	movabsq	$9650791518880, %rax            # imm = 0x8C7000012A0
	movq	%rax, -3152(%rbp)
	movabsq	$3925600113190, %rax            # imm = 0x39200001226
	movq	%rax, -3144(%rbp)
	movabsq	$6051608922703, %rax            # imm = 0x58100000A4F
	movq	%rax, -3136(%rbp)
	movabsq	$17141214480248, %rax           # imm = 0xF9700000778
	movq	%rax, -3128(%rbp)
	movabsq	$4380866645276, %rax            # imm = 0x3FC00000D1C
	movq	%rax, -3120(%rbp)
	movabsq	$4080218933545, %rax            # imm = 0x3B600000929
	movq	%rax, -3112(%rbp)
	movabsq	$4797478471262, %rax            # imm = 0x45D0000065E
	movq	%rax, -3104(%rbp)
	movabsq	$21234318311482, %rax           # imm = 0x13500000003A
	movq	%rax, -3096(%rbp)
	movabsq	$21191368641759, %rax           # imm = 0x134600000CDF
	movq	%rax, -3088(%rbp)
	movabsq	$12760347837258, %rax           # imm = 0xB9B0000034A
	movq	%rax, -3080(%rbp)
	movabsq	$3848290700329, %rax            # imm = 0x38000000C29
	movq	%rax, -3072(%rbp)
	movabsq	$6859062774344, %rax            # imm = 0x63D00000A48
	movq	%rax, -3064(%rbp)
	movabsq	$16355235466193, %rax           # imm = 0xEE000000BD1
	movq	%rax, -3056(%rbp)
	movabsq	$2027224565358, %rax            # imm = 0x1D80000066E
	movq	%rax, -3048(%rbp)
	movabsq	$6167573037367, %rax            # imm = 0x59C00000137
	movq	%rax, -3040(%rbp)
	movabsq	$4153233380113, %rax            # imm = 0x3C700001311
	movq	%rax, -3032(%rbp)
	movabsq	$7352984011827, %rax            # imm = 0x6B000000433
	movq	%rax, -3024(%rbp)
	movabsq	$13155484832236, %rax           # imm = 0xBF7000011EC
	movq	%rax, -3016(%rbp)
	movabsq	$15831249457022, %rax           # imm = 0xE6600000F7E
	movq	%rax, -3008(%rbp)
	movabsq	$15577846384787, %rax           # imm = 0xE2B00000893
	movq	%rax, -3000(%rbp)
	movabsq	$13469017444200, %rax           # imm = 0xC4000000F68
	movq	%rax, -2992(%rbp)
	movabsq	$20358144985928, %rax           # imm = 0x128400000B48
	movq	%rax, -2984(%rbp)
	movabsq	$15122579849502, %rax           # imm = 0xDC10000011E
	movq	%rax, -2976(%rbp)
	movabsq	$15045270439513, %rax           # imm = 0xDAF00000659
	movq	%rax, -2968(%rbp)
	movabsq	$9444633085808, %rax            # imm = 0x89700000770
	movq	%rax, -2960(%rbp)
	movabsq	$19924353288983, %rax           # imm = 0x121F00000B17
	movq	%rax, -2952(%rbp)
	movabsq	$12283606468003, %rax           # imm = 0xB2C000005A3
	movq	%rax, -2944(%rbp)
	movabsq	$20882130995365, %rax           # imm = 0x12FE000008A5
	movq	%rax, -2936(%rbp)
	movabsq	$219043333574, %rax             # imm = 0x33000005C6
	movq	%rax, -2928(%rbp)
	movabsq	$11665131180278, %rax           # imm = 0xA9C000010F6
	movq	%rax, -2920(%rbp)
	movabsq	$3165390898600, %rax            # imm = 0x2E1000005A8
	movq	%rax, -2912(%rbp)
	movabsq	$9539122366003, %rax            # imm = 0x8AD00000633
	movq	%rax, -2904(%rbp)
	movabsq	$249108106180, %rax             # imm = 0x3A00000BC4
	movq	%rax, -2896(%rbp)
	movabsq	$14156212211015, %rax           # imm = 0xCE000000D47
	movq	%rax, -2888(%rbp)
	movabsq	$5763846115373, %rax            # imm = 0x53E0000102D
	movq	%rax, -2880(%rbp)
	movabsq	$10861972295998, %rax           # imm = 0x9E10000113E
	movq	%rax, -2872(%rbp)
	movabsq	$2959232467989, %rax            # imm = 0x2B100000415
	movq	%rax, -2864(%rbp)
	movabsq	$1915555415444, %rax            # imm = 0x1BE00000594
	movq	%rax, -2856(%rbp)
	movabsq	$18867791333458, %rax           # imm = 0x112900000852
	movq	%rax, -2848(%rbp)
	movabsq	$9496172693969, %rax            # imm = 0x8A3000009D1
	movq	%rax, -2840(%rbp)
	movabsq	$12416750457049, %rax           # imm = 0xB4B000010D9
	movq	%rax, -2832(%rbp)
	movabsq	$9809705308245, %rax            # imm = 0x8EC00001055
	movq	%rax, -2824(%rbp)
	movabsq	$14632953580268, %rax           # imm = 0xD4F00000AEC
	movq	%rax, -2816(%rbp)
	movabsq	$17476221931117, %rax           # imm = 0xFE500000E6D
	movq	%rax, -2808(%rbp)
	movabsq	$12837657251358, %rax           # imm = 0xBAD00000E1E
	movq	%rax, -2800(%rbp)
	movabsq	$7975754269605, %rax            # imm = 0x741000003A5
	movq	%rax, -2792(%rbp)
	movabsq	$15199889264159, %rax           # imm = 0xDD300000E1F
	movq	%rax, -2784(%rbp)
	movabsq	$11205569678739, %rax           # imm = 0xA3100000D93
	movq	%rax, -2776(%rbp)
	movabsq	$10703058505725, %rax           # imm = 0x9BC00000FFD
	movq	%rax, -2768(%rbp)
	movabsq	$5587752454509, %rax            # imm = 0x5150000096D
	movq	%rax, -2760(%rbp)
	movabsq	$15406047691503, %rax           # imm = 0xE03000002EF
	movq	%rax, -2752(%rbp)
	movabsq	$14461154887951, %rax           # imm = 0xD270000090F
	movq	%rax, -2744(%rbp)
	movabsq	$4007204487355, %rax            # imm = 0x3A5000000BB
	movq	%rax, -2736(%rbp)
	movabsq	$6425271077302, %rax            # imm = 0x5D8000009B6
	movq	%rax, -2728(%rbp)
	movabsq	$18214956306617, %rax           # imm = 0x1091000010B9
	movq	%rax, -2720(%rbp)
	movabsq	$16247861283683, %rax           # imm = 0xEC700000B63
	movq	%rax, -2712(%rbp)
	movabsq	$20061792241343, %rax           # imm = 0x123F000006BF
	movq	%rax, -2704(%rbp)
	movabsq	$15942918605774, %rax           # imm = 0xE8000000BCE
	movq	%rax, -2696(%rbp)
	movabsq	$1086626728555, %rax            # imm = 0xFD00000A6B
	movq	%rax, -2688(%rbp)
	movabsq	$17935783432304, %rax           # imm = 0x105000001070
	movq	%rax, -2680(%rbp)
	movabsq	$317827580281, %rax             # imm = 0x4A00000179
	movq	%rax, -2672(%rbp)
	movabsq	$2126008813446, %rax            # imm = 0x1EF00000786
	movq	%rax, -2664(%rbp)
	movabsq	$17892833759864, %rax           # imm = 0x104600001278
	movq	%rax, -2656(%rbp)
	movabsq	$5424543696741, %rax            # imm = 0x4EF00000765
	movq	%rax, -2648(%rbp)
	movabsq	$2147483650243, %rax            # imm = 0x1F4000008C3
	movq	%rax, -2640(%rbp)
	movabsq	$10389525889901, %rax           # imm = 0x9730000036D
	movq	%rax, -2632(%rbp)
	movabsq	$6511170421241, %rax            # imm = 0x5EC000001F9
	movq	%rax, -2624(%rbp)
	movabsq	$1241245552070, %rax            # imm = 0x12100000DC6
	movq	%rax, -2616(%rbp)
	movabsq	$2263447765244, %rax            # imm = 0x20F000000FC
	movq	%rax, -2608(%rbp)
	movabsq	$10191957395497, %rax           # imm = 0x94500000829
	movq	%rax, -2600(%rbp)
	movabsq	$17252883628096, %rax           # imm = 0xFB100000040
	movq	%rax, -2592(%rbp)
	movabsq	$14813342207294, %rax           # imm = 0xD7900000D3E
	movq	%rax, -2584(%rbp)
	movabsq	$18653042970169, %rax           # imm = 0x10F700000E39
	movq	%rax, -2576(%rbp)
	movabsq	$17489106830323, %rax           # imm = 0xFE8000003F3
	movq	%rax, -2568(%rbp)
	movabsq	$5480378269985, %rax            # imm = 0x4FC00000121
	movq	%rax, -2560(%rbp)
	movabsq	$18000207938235, %rax           # imm = 0x105F000002BB
	movq	%rax, -2552(%rbp)
	movabsq	$665719933224, %rax             # imm = 0x9B00000928
	movq	%rax, -2544(%rbp)
	movabsq	$20727512174324, %rax           # imm = 0x12DA00000EF4
	movq	%rax, -2536(%rbp)
	movabsq	$6416681141504, %rax            # imm = 0x5D600000500
	movq	%rax, -2528(%rbp)
	movabsq	$3118146261123, %rax            # imm = 0x2D600001083
	movq	%rax, -2520(%rbp)
	movabsq	$15642270893785, %rax           # imm = 0xE3A000006D9
	movq	%rax, -2512(%rbp)
	movabsq	$15393162792930, %rax           # imm = 0xE0000000FE2
	movq	%rax, -2504(%rbp)
	movabsq	$17935783429727, %rax           # imm = 0x10500000065F
	movq	%rax, -2496(%rbp)
	movabsq	$6412386175782, %rax            # imm = 0x5D500000B26
	movq	%rax, -2488(%rbp)
	movabsq	$11940009084549, %rax           # imm = 0xADC00000685
	movq	%rax, -2480(%rbp)
	movabsq	$14607183778322, %rax           # imm = 0xD4900001212
	movq	%rax, -2472(%rbp)
	movabsq	$18395344931159, %rax           # imm = 0x10BB00000957
	movq	%rax, -2464(%rbp)
	movabsq	$8259222110809, %rax            # imm = 0x78300000259
	movq	%rax, -2456(%rbp)
	movabsq	$6343666700493, %rax            # imm = 0x5C5000010CD
	movq	%rax, -2448(%rbp)
	movabsq	$15925738736799, %rax           # imm = 0xE7C00000C9F
	movq	%rax, -2440(%rbp)
	movabsq	$9118215573588, %rax            # imm = 0x84B00001054
	movq	%rax, -2432(%rbp)
	movabsq	$13318693586983, %rax           # imm = 0xC1D00000827
	movq	%rax, -2424(%rbp)
	movabsq	$11184094838819, %rax           # imm = 0xA2C00000023
	movq	%rax, -2416(%rbp)
	movabsq	$12781822674627, %rax           # imm = 0xBA0000006C3
	movq	%rax, -2408(%rbp)
	movabsq	$3423088937076, %rax            # imm = 0x31D00000874
	movq	%rax, -2400(%rbp)
	movabsq	$14048838029242, %rax           # imm = 0xCC700000FBA
	movq	%rax, -2392(%rbp)
	movabsq	$20104741914118, %rax           # imm = 0x124900000606
	movq	%rax, -2384(%rbp)
	movabsq	$317827580741, %rax             # imm = 0x4A00000345
	movq	%rax, -2376(%rbp)
	movabsq	$6592774801830, %rax            # imm = 0x5FF000009A6
	movq	%rax, -2368(%rbp)
	movabsq	$9646496547081, %rax            # imm = 0x8C600000109
	movq	%rax, -2360(%rbp)
	movabsq	$11347303597354, %rax           # imm = 0xA520000052A
	movq	%rax, -2352(%rbp)
	movabsq	$17798344479173, %rax           # imm = 0x1030000011C5
	movq	%rax, -2344(%rbp)
	movabsq	$20675972566152, %rax           # imm = 0x12CE00000C88
	movq	%rax, -2336(%rbp)
	movabsq	$19636590479581, %rax           # imm = 0x11DC000008DD
	movq	%rax, -2328(%rbp)
	movabsq	$3685081941470, %rax            # imm = 0x35A000005DE
	movq	%rax, -2320(%rbp)
	movabsq	$11098195494905, %rax           # imm = 0xA18000007F9
	movq	%rax, -2312(%rbp)
	movabsq	$14353780704208, %rax           # imm = 0xD0E000003D0
	movq	%rax, -2304(%rbp)
	movabsq	$1408749273142, %rax            # imm = 0x14800000036
	movq	%rax, -2296(%rbp)
	movabsq	$2624225018620, %rax            # imm = 0x263000002FC
	movq	%rax, -2288(%rbp)
	movabsq	$19928648256381, %rax           # imm = 0x122000000B7D
	movq	%rax, -2280(%rbp)
	movabsq	$20963735375476, %rax           # imm = 0x131100000E74
	movq	%rax, -2272(%rbp)
	movabsq	$18794776887931, %rax           # imm = 0x11180000027B
	movq	%rax, -2264(%rbp)
	movabsq	$1958505090569, %rax            # imm = 0x1C800000E09
	movq	%rax, -2256(%rbp)
	movabsq	$11454677779497, %rax           # imm = 0xA6B00000429
	movq	%rax, -2248(%rbp)
	movabsq	$8753143352716, %rax            # imm = 0x7F600000D8C
	movq	%rax, -2240(%rbp)
	movabsq	$20005957667339, %rax           # imm = 0x123200000A0B
	movq	%rax, -2232(%rbp)
	movabsq	$21333102559950, %rax           # imm = 0x1367000002CE
	movq	%rax, -2224(%rbp)
	movabsq	$16728897621231, %rax           # imm = 0xF3700000CEF
	movq	%rax, -2216(%rbp)
	movabsq	$2589865281445, %rax            # imm = 0x25B000007A5
	movq	%rax, -2208(%rbp)
	movabsq	$3508988284908, %rax            # imm = 0x33100000FEC
	movq	%rax, -2200(%rbp)
	movabsq	$19804094203917, %rax           # imm = 0x12030000080D
	movq	%rax, -2192(%rbp)
	movabsq	$20512763809278, %rax           # imm = 0x12A800000DFE
	movq	%rax, -2184(%rbp)
	movabsq	$16612933504693, %rax           # imm = 0xF1C00000EB5
	movq	%rax, -2176(%rbp)
	movabsq	$6588479833188, %rax            # imm = 0x5FE00000464
	movq	%rax, -2168(%rbp)
	movabsq	$6382321404958, %rax            # imm = 0x5CE00000C1E
	movq	%rax, -2160(%rbp)
	movabsq	$16797617094673, %rax           # imm = 0xF4700000011
	movq	%rax, -2152(%rbp)
	movabsq	$17871358918790, %rax           # imm = 0x104100000086
	movq	%rax, -2144(%rbp)
	movabsq	$12253541697278, %rax           # imm = 0xB25000006FE
	movq	%rax, -2136(%rbp)
	movabsq	$18438294602975, %rax           # imm = 0x10C5000004DF
	movq	%rax, -2128(%rbp)
	movabsq	$5149665791707, %rax            # imm = 0x4AF00000EDB
	movq	%rax, -2120(%rbp)
	movabsq	$3843995732573, %rax            # imm = 0x37F00000A5D
	movq	%rax, -2112(%rbp)
	movabsq	$20315195312060, %rax           # imm = 0x127A000007BC
	movq	%rax, -2104(%rbp)
	movabsq	$11420318042535, %rax           # imm = 0xA63000009A7
	movq	%rax, -2096(%rbp)
	movabsq	$11781095293333, %rax           # imm = 0xAB700000195
	movq	%rax, -2088(%rbp)
	movabsq	$10900626998508, %rax           # imm = 0x9EA000004EC
	movq	%rax, -2080(%rbp)
	movabsq	$13937168877283, %rax           # imm = 0xCAD000006E3
	movq	%rax, -2072(%rbp)
	movabsq	$3758096386277, %rax            # imm = 0x36B000008E5
	movq	%rax, -2064(%rbp)
	movabsq	$2847563318004, %rax            # imm = 0x297000002F4
	movq	%rax, -2056(%rbp)
	movabsq	$3113851291343, %rax            # imm = 0x2D5000006CF
	movq	%rax, -2048(%rbp)
	movabsq	$944892808445, %rax             # imm = 0xDC00000CFD
	movq	%rax, -2040(%rbp)
	movabsq	$4780298601623, %rax            # imm = 0x45900000497
	movq	%rax, -2032(%rbp)
	movabsq	$16939351019396, %rax           # imm = 0xF6800000F84
	movq	%rax, -2024(%rbp)
	movabsq	$8040178781378, %rax            # imm = 0x75000000CC2
	movq	%rax, -2016(%rbp)
	movabsq	$17368847748965, %rax           # imm = 0xFCC00000F65
	movq	%rax, -2008(%rbp)
	movabsq	$5970004544817, %rax            # imm = 0x56E00000D31
	movq	%rax, -2000(%rbp)
	movabsq	$11905649344937, %rax           # imm = 0xAD4000001A9
	movq	%rax, -1992(%rbp)
	movabsq	$8276401980907, %rax            # imm = 0x787000005EB
	movq	%rax, -1984(%rbp)
	movabsq	$11338713666222, %rax           # imm = 0xA50000012AE
	movq	%rax, -1976(%rbp)
	movabsq	$11029476017536, %rax           # imm = 0xA0800000580
	movq	%rax, -1968(%rbp)
	movabsq	$1945620189843, %rax            # imm = 0x1C500001293
	movq	%rax, -1960(%rbp)
	movabsq	$399431960716, %rax             # imm = 0x5D0000088C
	movq	%rax, -1952(%rbp)
	movabsq	$17682380360156, %rax           # imm = 0x1015000009DC
	movq	%rax, -1944(%rbp)
	movabsq	$7782480744265, %rax            # imm = 0x71400000F49
	movq	%rax, -1936(%rbp)
	movabsq	$10892037066889, %rax           # imm = 0x9E800001089
	movq	%rax, -1928(%rbp)
	movabsq	$15384572854778, %rax           # imm = 0xDFE000001FA
	movq	%rax, -1920(%rbp)
	movabsq	$9663676418301, %rax            # imm = 0x8CA000008FD
	movq	%rax, -1912(%rbp)
	movabsq	$20332375184196, %rax           # imm = 0x127E00001344
	movq	%rax, -1904(%rbp)
	movabsq	$605590391885, %rax             # imm = 0x8D00000C4D
	movq	%rax, -1896(%rbp)
	movabsq	$15934328669592, %rax           # imm = 0xE7E00000598
	movq	%rax, -1888(%rbp)
	movabsq	$16458314681181, %rax           # imm = 0xEF800000B5D
	movq	%rax, -1880(%rbp)
	movabsq	$8568459760425, %rax            # imm = 0x7CB00001329
	movq	%rax, -1872(%rbp)
	movabsq	$20963735376274, %rax           # imm = 0x131100001192
	movq	%rax, -1864(%rbp)
	movabsq	$12803297513889, %rax           # imm = 0xBA5000011A1
	movq	%rax, -1856(%rbp)
	movabsq	$3710851746642, %rax            # imm = 0x36000000B52
	movq	%rax, -1848(%rbp)
	movabsq	$9388798513690, %rax            # imm = 0x88A0000121A
	movq	%rax, -1840(%rbp)
	movabsq	$2783138812552, %rax            # imm = 0x28800001288
	movq	%rax, -1832(%rbp)
	movabsq	$8087423420058, %rax            # imm = 0x75B0000069A
	movq	%rax, -1824(%rbp)
	movabsq	$15603616189508, %rax           # imm = 0xE3100000C44
	movq	%rax, -1816(%rbp)
	movabsq	$17587891077894, %rax           # imm = 0xFFF00000306
	movq	%rax, -1808(%rbp)
	movabsq	$11746735558413, %rax           # imm = 0xAAF00000F0D
	movq	%rax, -1800(%rbp)
	movabsq	$6451040881084, %rax            # imm = 0x5DE000009BC
	movq	%rax, -1792(%rbp)
	movabsq	$13731010448889, %rax           # imm = 0xC7D00000DF9
	movq	%rax, -1784(%rbp)
	movabsq	$15221364099796, %rax           # imm = 0xDD800000AD4
	movq	%rax, -1776(%rbp)
	movabsq	$5463198402821, %rax            # imm = 0x4F800000905
	movq	%rax, -1768(%rbp)
	movabsq	$3895535341613, %rax            # imm = 0x38B0000102D
	movq	%rax, -1760(%rbp)
	movabsq	$14778982467442, %rax           # imm = 0xD7100000772
	movq	%rax, -1752(%rbp)
	movabsq	$9229884722510, %rax            # imm = 0x86500000D4E
	movq	%rax, -1744(%rbp)
	movabsq	$5450313502647, %rax            # imm = 0x4F500000FB7
	movq	%rax, -1736(%rbp)
	movabsq	$4861902979528, %rax            # imm = 0x46C000001C8
	movq	%rax, -1728(%rbp)
	movabsq	$16045997822050, %rax           # imm = 0xE9800001062
	movq	%rax, -1720(%rbp)
	movabsq	$5540507814616, %rax            # imm = 0x50A00000AD8
	movq	%rax, -1712(%rbp)
	movabsq	$11531987191833, %rax           # imm = 0xA7D00000819
	movq	%rax, -1704(%rbp)
	movabsq	$17154099383037, %rax           # imm = 0xF9A00000AFD
	movq	%rax, -1696(%rbp)
	movabsq	$10075993279002, %rax           # imm = 0x92A00000A1A
	movq	%rax, -1688(%rbp)
	movabsq	$9753870730281, %rax            # imm = 0x8DF00000429
	movq	%rax, -1680(%rbp)
	movabsq	$1245540517736, %rax            # imm = 0x12200000768
	movq	%rax, -1672(%rbp)
	movabsq	$3762391355498, %rax            # imm = 0x36C0000106A
	movq	%rax, -1664(%rbp)
	movabsq	$3942779978421, %rax            # imm = 0x396000002B5
	movq	%rax, -1656(%rbp)
	movabsq	$10041633541396, %rax           # imm = 0x92200000D14
	movq	%rax, -1648(%rbp)
	movabsq	$7808250545916, %rax            # imm = 0x71A000006FC
	movq	%rax, -1640(%rbp)
	movabsq	$4887672786387, %rax            # imm = 0x47200000DD3
	movq	%rax, -1632(%rbp)
	movabsq	$7623566951460, %rax            # imm = 0x6EF00000424
	movq	%rax, -1624(%rbp)
	movabsq	$18833431593872, %rax           # imm = 0x112100000390
	movq	%rax, -1616(%rbp)
	movabsq	$13408887902068, %rax           # imm = 0xC3200000F74
	movq	%rax, -1608(%rbp)
	movabsq	$4385161611031, %rax            # imm = 0x3FD00000717
	movq	%rax, -1600(%rbp)
	movabsq	$16256451217371, %rax           # imm = 0xEC9000007DB
	movq	%rax, -1592(%rbp)
	movabsq	$16329465661010, %rax           # imm = 0xEDA00000652
	movq	%rax, -1584(%rbp)
	movabsq	$20499878904418, %rax           # imm = 0x12A500000262
	movq	%rax, -1576(%rbp)
	movabsq	$21440476742622, %rax           # imm = 0x1380000003DE
	movq	%rax, -1568(%rbp)
	movabsq	$9882719752305, %rax            # imm = 0x8FD00001071
	movq	%rax, -1560(%rbp)
	movabsq	$20860656156908, %rax           # imm = 0x12F9000000EC
	movq	%rax, -1552(%rbp)
	movabsq	$15543486647526, %rax           # imm = 0xE2300000CE6
	movq	%rax, -1544(%rbp)
	movabsq	$17940078397077, %rax           # imm = 0x105100000695
	movq	%rax, -1536(%rbp)
	movabsq	$10548439680936, %rax           # imm = 0x998000007A8
	movq	%rax, -1528(%rbp)
	movabsq	$1215475749365, %rax            # imm = 0x11B000011F5
	movq	%rax, -1520(%rbp)
	movabsq	$9259949492237, %rax            # imm = 0x86C0000080D
	movq	%rax, -1512(%rbp)
	movabsq	$17506286702268, %rax           # imm = 0xFEC00000EBC
	movq	%rax, -1504(%rbp)
	movabsq	$700079670158, %rax             # imm = 0xA30000038E
	movq	%rax, -1496(%rbp)
	movabsq	$9732395897571, %rax            # imm = 0x8DA000012E3
	movq	%rax, -1488(%rbp)
	movabsq	$10393820859157, %rax           # imm = 0x97400000B15
	movq	%rax, -1480(%rbp)
	movabsq	$3307124821394, %rax            # imm = 0x30200000D92
	movq	%rax, -1472(%rbp)
	movabsq	$11278584122758, %rax           # imm = 0xA4200000D86
	movq	%rax, -1464(%rbp)
	movabsq	$9646496550705, %rax            # imm = 0x8C600000F31
	movq	%rax, -1456(%rbp)
	movabsq	$15792594747731, %rax           # imm = 0xE5D00000153
	movq	%rax, -1448(%rbp)
	movabsq	$2357937050080, %rax            # imm = 0x225000011E0
	movq	%rax, -1440(%rbp)
	movabsq	$12068858106394, %rax           # imm = 0xAFA0000121A
	movq	%rax, -1432(%rbp)
	movabsq	$9633611646598, %rax            # imm = 0x8C300000686
	movq	%rax, -1424(%rbp)
	movabsq	$3693671875515, %rax            # imm = 0x35C000003BB
	movq	%rax, -1416(%rbp)
	movabsq	$20830591386941, %rax           # imm = 0x12F20000053D
	movq	%rax, -1408(%rbp)
	movabsq	$19061064861237, %rax           # imm = 0x115600000635
	movq	%rax, -1400(%rbp)
	movabsq	$3405909066785, %rax            # imm = 0x31900000421
	movq	%rax, -1392(%rbp)
	movabsq	$20010252636548, %rax           # imm = 0x123300001184
	movq	%rax, -1384(%rbp)
	movabsq	$17158394351694, %rax           # imm = 0xF9B0000104E
	movq	%rax, -1376(%rbp)
	movabsq	$17811229379174, %rax           # imm = 0x103300000A66
	movq	%rax, -1368(%rbp)
	movabsq	$14667313319059, %rax           # imm = 0xD5700000C93
	movq	%rax, -1360(%rbp)
	movabsq	$12579959214552, %rax           # imm = 0xB71000011D8
	movq	%rax, -1352(%rbp)
	movabsq	$19894288519434, %rax           # imm = 0x12180000110A
	movq	%rax, -1344(%rbp)
	movabsq	$18154826764032, %rax           # imm = 0x108300000F00
	movq	%rax, -1336(%rbp)
	movabsq	$2121713848933, %rax            # imm = 0x1EE00001265
	movq	%rax, -1328(%rbp)
	movabsq	$17841294151019, %rax           # imm = 0x103A00000D6B
	movq	%rax, -1320(%rbp)
	movabsq	$17248588663910, %rax           # imm = 0xFB000000C66
	movq	%rax, -1312(%rbp)
	movabsq	$15088220115294, %rax           # imm = 0xDB90000115E
	movq	%rax, -1304(%rbp)
	movabsq	$3496103380439, %rax            # imm = 0x32E000005D7
	movq	%rax, -1296(%rbp)
	movabsq	$18098992186020, %rax           # imm = 0x1076000002A4
	movq	%rax, -1288(%rbp)
	movabsq	$19125489370654, %rax           # imm = 0x11650000061E
	movq	%rax, -1280(%rbp)
	movabsq	$20504173871276, %rax           # imm = 0x12A6000000AC
	movq	%rax, -1272(%rbp)
	movabsq	$1013612286739, %rax            # imm = 0xEC00001313
	movq	%rax, -1264(%rbp)
	movabsq	$38654708453, %rax              # imm = 0x900000AE5
	movq	%rax, -1256(%rbp)
	movabsq	$15255723839512, %rax           # imm = 0xDE000001018
	movq	%rax, -1248(%rbp)
	movabsq	$12300786335827, %rax           # imm = 0xB3000000053
	movq	%rax, -1240(%rbp)
	movabsq	$8757438321052, %rax            # imm = 0x7F70000119C
	movq	%rax, -1232(%rbp)
	movabsq	$3620657434373, %rax            # imm = 0x34B00000F05
	movq	%rax, -1224(%rbp)
	movabsq	$6713033885436, %rax            # imm = 0x61B000006FC
	movq	%rax, -1216(%rbp)
	movabsq	$12275016534102, %rax           # imm = 0xB2A00000856
	movq	%rax, -1208(%rbp)
	movabsq	$11209864644657, %rax           # imm = 0xA3200000831
	movq	%rax, -1200(%rbp)
	movabsq	$18966575583478, %rax           # imm = 0x1140000010F6
	movq	%rax, -1192(%rbp)
	movabsq	$19241453487520, %rax           # imm = 0x1180000005A0
	movq	%rax, -1184(%rbp)
	movabsq	$18657337937538, %rax           # imm = 0x10F800000E82
	movq	%rax, -1176(%rbp)
	movabsq	$2409476656073, %rax            # imm = 0x23100000BC9
	movq	%rax, -1168(%rbp)
	movabsq	$6597069770181, %rax            # imm = 0x60000000DC5
	movq	%rax, -1160(%rbp)
	movabsq	$12244951764081, %rax           # imm = 0xB2300000C71
	movq	%rax, -1152(%rbp)
	movabsq	$932007906671, %rax             # imm = 0xD900000D6F
	movq	%rax, -1144(%rbp)
	movabsq	$16071767622409, %rax           # imm = 0xE9E00000309
	movq	%rax, -1136(%rbp)
	movabsq	$571230651473, %rax             # imm = 0x8500000451
	movq	%rax, -1128(%rbp)
	movabsq	$19786914336331, %rax           # imm = 0x11FF00000E4B
	movq	%rax, -1120(%rbp)
	movabsq	$14611478743171, %rax           # imm = 0xD4A00000883
	movq	%rax, -1112(%rbp)
	movabsq	$2778843841493, %rax            # imm = 0x287000003D5
	movq	%rax, -1104(%rbp)
	movabsq	$4166118279423, %rax            # imm = 0x3CA000008FF
	movq	%rax, -1096(%rbp)
	movabsq	$10758893077380, %rax           # imm = 0x9C900000384
	movq	%rax, -1088(%rbp)
	movabsq	$9775345568408, %rax            # imm = 0x8E400000A98
	movq	%rax, -1080(%rbp)
	movabsq	$18717467477139, %rax           # imm = 0x110600000493
	movq	%rax, -1072(%rbp)
	movabsq	$13696650709730, %rax           # imm = 0xC7500000AE2
	movq	%rax, -1064(%rbp)
	movabsq	$3186865734608, %rax            # imm = 0x2E6000003D0
	movq	%rax, -1056(%rbp)
	movabsq	$7060926235796, %rax            # imm = 0x66C00000494
	movq	%rax, -1048(%rbp)
	movabsq	$5244155070792, %rax            # imm = 0x4C500000948
	movq	%rax, -1040(%rbp)
	movabsq	$1799591300935, %rax            # imm = 0x1A300000F47
	movq	%rax, -1032(%rbp)
	movabsq	$9053791064952, %rax            # imm = 0x83C00001378
	movq	%rax, -1024(%rbp)
	movabsq	$15728170240812, %rax           # imm = 0xE4E00000B2C
	movq	%rax, -1016(%rbp)
	movabsq	$15689515536629, %rax           # imm = 0xE45000010F5
	movq	%rax, -1008(%rbp)
	movabsq	$8916352110176, %rax            # imm = 0x81C00000E60
	movq	%rax, -1000(%rbp)
	movabsq	$17763984739427, %rax           # imm = 0x102800000C63
	movq	%rax, -992(%rbp)
	movabsq	$5673651801831, %rax            # imm = 0x52900000EE7
	movq	%rax, -984(%rbp)
	movabsq	$5845450494452, %rax            # imm = 0x551000011F4
	movq	%rax, -976(%rbp)
	movabsq	$8972186684765, %rax            # imm = 0x82900000D5D
	movq	%rax, -968(%rbp)
	movabsq	$9500467659686, %rax            # imm = 0x8A4000003A6
	movq	%rax, -960(%rbp)
	movabsq	$18983755449024, %rax           # imm = 0x1144000002C0
	movq	%rax, -952(%rbp)
	movabsq	$4363686776129, %rax            # imm = 0x3F800000D41
	movq	%rax, -944(%rbp)
	movabsq	$16372415336500, %rax           # imm = 0xEE400001034
	movq	%rax, -936(%rbp)
	movabsq	$4350801872845, %rax            # imm = 0x3F5000007CD
	movq	%rax, -928(%rbp)
	movabsq	$4870492916527, %rax            # imm = 0x46E00000B2F
	movq	%rax, -920(%rbp)
	movabsq	$2426656524865, %rax            # imm = 0x23500000A41
	movq	%rax, -912(%rbp)
	movabsq	$8581344661643, %rax            # imm = 0x7CE0000108B
	movq	%rax, -904(%rbp)
	movabsq	$3307124818412, %rax            # imm = 0x302000001EC
	movq	%rax, -896(%rbp)
	movabsq	$21144123999417, %rax           # imm = 0x133B000004B9
	movq	%rax, -888(%rbp)
	movabsq	$4621384813740, %rax            # imm = 0x43400000CAC
	movq	%rax, -880(%rbp)
	movabsq	$11596411701092, %rax           # imm = 0xA8C00000764
	movq	%rax, -872(%rbp)
	movabsq	$1554778165248, %rax            # imm = 0x16A00001000
	movq	%rax, -864(%rbp)
	movabsq	$15500536976226, %rax           # imm = 0xE1900001362
	movq	%rax, -856(%rbp)
	movabsq	$1511828490691, %rax            # imm = 0x160000009C3
	movq	%rax, -848(%rbp)
	movabsq	$996432415724, %rax             # imm = 0xE800000BEC
	movq	%rax, -840(%rbp)
	movabsq	$18734647347001, %rax           # imm = 0x110A00000739
	movq	%rax, -832(%rbp)
	movabsq	$9680856286363, %rax            # imm = 0x8CE0000049B
	movq	%rax, -824(%rbp)
	movabsq	$12644383722400, %rax           # imm = 0xB8000000BA0
	movq	%rax, -816(%rbp)
	movabsq	$11008001181297, %rax           # imm = 0xA0300000671
	movq	%rax, -808(%rbp)
	movabsq	$12902081761900, %rax           # imm = 0xBBC0000126C
	movq	%rax, -800(%rbp)
	movabsq	$3118146258486, %rax            # imm = 0x2D600000636
	movq	%rax, -792(%rbp)
	movabsq	$9088150799479, %rax            # imm = 0x84400000477
	movq	%rax, -784(%rbp)
	movabsq	$3929895078468, %rax            # imm = 0x39300000A44
	movq	%rax, -776(%rbp)
	movabsq	$5106716119760, %rax            # imm = 0x4A5000012D0
	movq	%rax, -768(%rbp)
	movabsq	$17772574673324, %rax           # imm = 0x102A000009AC
	movq	%rax, -760(%rbp)
	movabsq	$20237885901900, %rax           # imm = 0x126800000C4C
	movq	%rax, -752(%rbp)
	movabsq	$15139759720666, %rax           # imm = 0xDC5000008DA
	movq	%rax, -744(%rbp)
	movabsq	$974957580596, %rax             # imm = 0xE300001134
	movq	%rax, -736(%rbp)
	movabsq	$11948599017571, %rax           # imm = 0xADE00000063
	movq	%rax, -728(%rbp)
	movabsq	$11746735557575, %rax           # imm = 0xAAF00000BC7
	movq	%rax, -720(%rbp)
	movabsq	$15311558414625, %rax           # imm = 0xDED00001121
	movq	%rax, -712(%rbp)
	movabsq	$11849814771025, %rax           # imm = 0xAC700000551
	movq	%rax, -704(%rbp)
	movabsq	$15745350108610, %rax           # imm = 0xE52000005C2
	movq	%rax, -696(%rbp)
	movabsq	$18532783886431, %rax           # imm = 0x10DB0000105F
	movq	%rax, -688(%rbp)
	movabsq	$6073083756944, %rax            # imm = 0x58600000190
	movq	%rax, -680(%rbp)
	movabsq	$19877108649254, %rax           # imm = 0x121400000D26
	movq	%rax, -672(%rbp)
	movabsq	$20959440408732, %rax           # imm = 0x13100000109C
	movq	%rax, -664(%rbp)
	movabsq	$2452426327495, %rax            # imm = 0x23B000005C7
	movq	%rax, -656(%rbp)
	movabsq	$15874199130453, %rax           # imm = 0xE7000001155
	movq	%rax, -648(%rbp)
	movabsq	$17252883630237, %rax           # imm = 0xFB10000089D
	movq	%rax, -640(%rbp)
	movabsq	$11940009085879, %rax           # imm = 0xADC00000BB7
	movq	%rax, -632(%rbp)
	movabsq	$14542759267592, %rax           # imm = 0xD3A00000D08
	movq	%rax, -624(%rbp)
	movabsq	$7073811140277, %rax            # imm = 0x66F00000EB5
	movq	%rax, -616(%rbp)
	movabsq	$18829136627754, %rax           # imm = 0x11200000082A
	movq	%rax, -608(%rbp)
	movabsq	$5957119642586, %rax            # imm = 0x56B00000BDA
	movq	%rax, -600(%rbp)
	movabsq	$9972914063918, %rax            # imm = 0x91200000A2E
	movq	%rax, -592(%rbp)
	movabsq	$11179799872571, %rax           # imm = 0xA2B0000043B
	movq	%rax, -584(%rbp)
	movabsq	$1632087573672, %rax            # imm = 0x17C000004A8
	movq	%rax, -576(%rbp)
	movabsq	$4333622006461, %rax            # imm = 0x3F1000012BD
	movq	%rax, -568(%rbp)
	movabsq	$9028021260562, %rax            # imm = 0x83600001112
	movq	%rax, -560(%rbp)
	movabsq	$2551210577284, %rax            # imm = 0x25200000D84
	movq	%rax, -552(%rbp)
	movabsq	$3912715208147, %rax            # imm = 0x38F000005D3
	movq	%rax, -544(%rbp)
	movabsq	$5244155070722, %rax            # imm = 0x4C500000902
	movq	%rax, -536(%rbp)
	movabsq	$8349416425936, %rax            # imm = 0x798000009D0
	movq	%rax, -528(%rbp)
	movabsq	$18107582120575, %rax           # imm = 0x10780000027F
	movq	%rax, -520(%rbp)
	movabsq	$18111877090406, %rax           # imm = 0x107900000C66
	movq	%rax, -512(%rbp)
	movabsq	$3556232921938, %rax            # imm = 0x33C00000352
	movq	%rax, -504(%rbp)
	movabsq	$11854109741182, %rax           # imm = 0xAC80000107E
	movq	%rax, -496(%rbp)
	movabsq	$14048838026298, %rax           # imm = 0xCC70000043A
	movq	%rax, -488(%rbp)
	movabsq	$20083267081022, %rax           # imm = 0x12440000133E
	movq	%rax, -480(%rbp)
	movabsq	$16372415333151, %rax           # imm = 0xEE40000031F
	movq	%rax, -472(%rbp)
	movabsq	$5587752455515, %rax            # imm = 0x51500000D5B
	movq	%rax, -464(%rbp)
	movabsq	$893353198179, %rax             # imm = 0xD000000263
	movq	%rax, -456(%rbp)
	movabsq	$20104741916100, %rax           # imm = 0x124900000DC4
	movq	%rax, -448(%rbp)
	movabsq	$18421114735157, %rax           # imm = 0x10C100000A35
	movq	%rax, -440(%rbp)
	movabsq	$3908420241996, %rax            # imm = 0x38E00000A4C
	movq	%rax, -432(%rbp)
	movabsq	$16273631085312, %rax           # imm = 0xECD00000300
	movq	%rax, -424(%rbp)
	movabsq	$94489284003, %rax              # imm = 0x1600000DA3
	movq	%rax, -416(%rbp)
	movabsq	$19348827670893, %rax           # imm = 0x11990000096D
	movq	%rax, -408(%rbp)
	movabsq	$6674379182651, %rax            # imm = 0x6120000123B
	movq	%rax, -400(%rbp)
	movabsq	$9006546422514, %rax            # imm = 0x83100000AF2
	movq	%rax, -392(%rbp)
	movabsq	$18056042514141, %rax           # imm = 0x106C000006DD
	movq	%rax, -384(%rbp)
	movabsq	$14010183320884, %rax           # imm = 0xCBE00000534
	movq	%rax, -376(%rbp)
	movabsq	$17849884083502, %rax           # imm = 0x103C0000052E
	movq	%rax, -368(%rbp)
	movabsq	$6820408069253, %rax            # imm = 0x63400000C85
	movq	%rax, -360(%rbp)
	movabsq	$1400159343179, %rax            # imm = 0x1460000124B
	movq	%rax, -352(%rbp)
	movabsq	$7851200219039, %rax            # imm = 0x7240000079F
	movq	%rax, -344(%rbp)
	movabsq	$605590392669, %rax             # imm = 0x8D00000F5D
	movq	%rax, -336(%rbp)
	movabsq	$14306536064724, %rax           # imm = 0xD03000006D4
	movq	%rax, -328(%rbp)
	movabsq	$9758165700173, %rax            # imm = 0x8E000000E4D
	movq	%rax, -320(%rbp)
	movabsq	$15874199127421, %rax           # imm = 0xE700000057D
	movq	%rax, -312(%rbp)
	movabsq	$2461016264687, %rax            # imm = 0x23D00000FEF
	movq	%rax, -304(%rbp)
	movabsq	$20989505178831, %rax           # imm = 0x131700000CCF
	movq	%rax, -296(%rbp)
	movabsq	$4956392261114, %rax            # imm = 0x482000005FA
	movq	%rax, -288(%rbp)
	movabsq	$11596411700727, %rax           # imm = 0xA8C000005F7
	movq	%rax, -280(%rbp)
	movabsq	$12081743006812, %rax           # imm = 0xAFD00000C5C
	movq	%rax, -272(%rbp)
	movabsq	$15629385993666, %rax           # imm = 0xE3700000DC2
	movq	%rax, -264(%rbp)
	movabsq	$9659381449287, %rax            # imm = 0x8C900000247
	movq	%rax, -256(%rbp)
	movabsq	$20761871912803, %rax           # imm = 0x12E200000F63
	movq	%rax, -248(%rbp)
	movabsq	$18305150617570, %rax           # imm = 0x10A6000007E2
	movq	%rax, -240(%rbp)
	movabsq	$7838315318309, %rax            # imm = 0x72100000C25
	movq	%rax, -232(%rbp)
	movabsq	$5355824219922, %rax            # imm = 0x4DF00000712
	movq	%rax, -224(%rbp)
	movabsq	$17364552780301, %rax           # imm = 0xFCB00000A0D
	movq	%rax, -216(%rbp)
	movabsq	$2521145805890, %rax            # imm = 0x24B00000C42
	movq	%rax, -208(%rbp)
	movabsq	$19099719567625, %rax           # imm = 0x115F00000909
	movq	%rax, -200(%rbp)
	movabsq	$17119739643134, %rax           # imm = 0xF92000004FE
	movq	%rax, -192(%rbp)
	movl	$1, %ebx
	callq	get_time@PLT
	movl	%eax, -124(%rbp)                # 4-byte Spill
	.p2align	4, 0x90
.LBB2_1:                                # %entry.while.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_3 Depth 2
                                        #       Child Loop BB2_12 Depth 3
                                        #       Child Loop BB2_15 Depth 3
                                        #       Child Loop BB2_18 Depth 3
                                        #       Child Loop BB2_24 Depth 3
                                        #       Child Loop BB2_27 Depth 3
	cmpl	$999, %ebx                      # imm = 0x3E7
	jg	.LBB2_29
# %bb.2:                                # %entry.while.start
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$999, -16(%rax)                 # imm = 0x3E7
	leal	-1(%rbx), %eax
	movq	%rax, -160(%rbp)                # 8-byte Spill
	movl	%ebx, %eax
	addl	%ebx, %ebx
	leal	-1(%rax,%rax), %eax
	movq	%rax, -152(%rbp)                # 8-byte Spill
	xorl	%edx, %edx
	movq	%rbx, -168(%rbp)                # 8-byte Spill
	jmp	.LBB2_3
	.p2align	4, 0x90
.LBB2_28:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.end.while.end.while.end
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movl	%ebx, (%rax)
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movl	%r15d, (%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movq	-168(%rbp), %rbx                # 8-byte Reload
	movl	%ebx, -16(%rax)
	movq	-176(%rbp), %rdx                # 8-byte Reload
	addl	%ebx, %edx
.LBB2_3:                                # %entry.while.start.while.cond
                                        #   Parent Loop BB2_1 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB2_12 Depth 3
                                        #       Child Loop BB2_15 Depth 3
                                        #       Child Loop BB2_18 Depth 3
                                        #       Child Loop BB2_24 Depth 3
                                        #       Child Loop BB2_27 Depth 3
	movl	$999, %eax                      # imm = 0x3E7
	cmpl	%eax, %edx
	jge	.LBB2_1
# %bb.4:                                # %entry.while.start.while.start
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	%rsp, %rax
	leaq	-16(%rax), %rcx
	movq	%rcx, %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	-160(%rbp), %rax                # 8-byte Reload
	addl	%edx, %eax
	cmpl	$999, %eax                      # imm = 0x3E7
	jle	.LBB2_6
# %bb.5:                                # %entry.while.start.while.start.if
                                        #   in Loop: Header=BB2_3 Depth=2
	movl	$999, (%rcx)                    # imm = 0x3E7
	jmp	.LBB2_7
	.p2align	4, 0x90
.LBB2_6:                                # %entry.while.start.while.start.else
                                        #   in Loop: Header=BB2_3 Depth=2
	movl	%eax, (%rcx)
.LBB2_7:                                # %entry.while.start.while.start.endif
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	%rsp, %rax
	leaq	-16(%rax), %rdi
	movq	%rdi, %rsp
	movl	$0, -16(%rax)
	movq	-152(%rbp), %rax                # 8-byte Reload
	addl	%edx, %eax
	cmpl	$1000, %eax                     # imm = 0x3E8
	jl	.LBB2_9
# %bb.8:                                # %entry.while.start.while.start.endif.if
                                        #   in Loop: Header=BB2_3 Depth=2
	movl	$999, (%rdi)                    # imm = 0x3E7
	jmp	.LBB2_10
	.p2align	4, 0x90
.LBB2_9:                                # %entry.while.start.while.start.endif.else
                                        #   in Loop: Header=BB2_3 Depth=2
	movl	%eax, (%rdi)
.LBB2_10:                               # %entry.while.start.while.start.endif.endif
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	%rsp, %rax
	leaq	-16(%rax), %rsi
	movq	%rsi, -96(%rbp)                 # 8-byte Spill
	movq	%rsi, %rsp
	movq	%rdx, -176(%rbp)                # 8-byte Spill
	movl	%edx, -16(%rax)
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsi
	movq	%rsi, -56(%rbp)                 # 8-byte Spill
	movq	%rsi, %rsp
	movl	(%rcx), %ecx
	movl	%ecx, -16(%rdx)
	movq	%rsp, %rsi
	leaq	-16(%rsi), %rsp
	movl	(%rdi), %ecx
	movl	%ecx, -16(%rsi)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rdi
	movq	%rdi, -112(%rbp)                # 8-byte Spill
	movq	%rdi, %rsp
	movl	$0, -16(%rcx)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rdi
	movq	%rdi, -88(%rbp)                 # 8-byte Spill
	movq	%rdi, %rsp
	movl	$0, -16(%rcx)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rdi
	movq	%rdi, -80(%rbp)                 # 8-byte Spill
	movq	%rdi, %rsp
	movl	$0, -16(%rcx)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rdi
	movq	%rdi, -144(%rbp)                # 8-byte Spill
	movq	%rdi, %rsp
	movl	-16(%rdx), %edi
	subl	-16(%rax), %edi
	incl	%edi
	movl	%edi, -16(%rcx)
	movq	%rsp, %rdi
	leaq	-16(%rdi), %rbx
	movq	%rbx, -104(%rbp)                # 8-byte Spill
	movq	%rbx, %rsp
	movl	-16(%rsi), %esi
	subl	-16(%rdx), %esi
	movl	%esi, -16(%rdi)
	movl	-16(%rcx), %edx
	movq	%rsp, %rsi
	movq	%rdx, -72(%rbp)                 # 8-byte Spill
	leaq	15(,%rdx,4), %rdx
	andq	$-16, %rdx
	subq	%rdx, %rsi
	movq	%rsi, -64(%rbp)                 # 8-byte Spill
	movq	%rsi, %rsp
	movl	-16(%rdi), %r12d
	movq	%rsp, %rsi
	leaq	15(,%r12,4), %rdx
	andq	$-16, %rdx
	subq	%rdx, %rsi
	movq	%rsi, -120(%rbp)                # 8-byte Spill
	movq	%rsi, %rsp
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsi
	movq	%rsi, -48(%rbp)                 # 8-byte Spill
	movq	%rsi, %rsp
	movl	$0, -16(%rdx)
	movl	-16(%rcx), %r13d
	movl	-16(%rax), %r15d
	xorl	%ebx, %ebx
	cmpl	%r13d, %ebx
	jge	.LBB2_13
	.p2align	4, 0x90
.LBB2_12:                               # %entry.while.start.while.start.endif.endif.while.start
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_3 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movl	%ebx, %edi
	movq	-72(%rbp), %rsi                 # 8-byte Reload
                                        # kill: def $esi killed $esi killed $rsi
	callq	__check_bounds__@PLT
	leaq	(%r15,%rbx), %r14
	movl	%r14d, %edi
	movl	$1000, %esi                     # imm = 0x3E8
	callq	__check_bounds__@PLT
	movslq	%r14d, %rax
	movl	-4184(%rbp,%rax,4), %eax
	movq	-64(%rbp), %rcx                 # 8-byte Reload
	movl	%eax, (%rcx,%rbx,4)
	incq	%rbx
	cmpl	%r13d, %ebx
	jl	.LBB2_12
.LBB2_13:                               # %entry.while.start.while.start.endif.endif.while.end
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movl	%ebx, (%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rcx
	movq	%rcx, -48(%rbp)                 # 8-byte Spill
	movq	%rcx, %rsp
	movl	$0, -16(%rax)
	movq	-104(%rbp), %rax                # 8-byte Reload
	movl	(%rax), %r13d
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movl	(%rax), %r15d
	incl	%r15d
	xorl	%ebx, %ebx
	cmpl	%r13d, %ebx
	jge	.LBB2_16
	.p2align	4, 0x90
.LBB2_15:                               # %entry.while.start.while.start.endif.endif.while.end.while.start
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_3 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movl	%ebx, %edi
	movl	%r12d, %esi
	callq	__check_bounds__@PLT
	leaq	(%r15,%rbx), %r14
	movl	%r14d, %edi
	movl	$1000, %esi                     # imm = 0x3E8
	callq	__check_bounds__@PLT
	movslq	%r14d, %rax
	movl	-4184(%rbp,%rax,4), %eax
	movq	-120(%rbp), %rcx                # 8-byte Reload
	movl	%eax, (%rcx,%rbx,4)
	incq	%rbx
	cmpl	%r13d, %ebx
	jl	.LBB2_15
.LBB2_16:                               # %entry.while.start.while.start.endif.endif.while.end.while.end
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	%r12, -56(%rbp)                 # 8-byte Spill
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movl	%ebx, (%rax)
	movq	-112(%rbp), %rdx                # 8-byte Reload
	movl	$0, (%rdx)
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movl	$0, (%rax)
	movq	-96(%rbp), %rcx                 # 8-byte Reload
	movl	(%rcx), %r15d
	movq	-80(%rbp), %rcx                 # 8-byte Reload
	movl	%r15d, (%rcx)
	movq	-144(%rbp), %rcx                # 8-byte Reload
	movl	(%rcx), %ecx
	movl	%ecx, -132(%rbp)                # 4-byte Spill
	movq	-104(%rbp), %rcx                # 8-byte Reload
	movl	(%rcx), %ecx
	movl	%ecx, -128(%rbp)                # 4-byte Spill
	movl	(%rdx), %ebx
	movl	(%rax), %r12d
	movq	-72(%rbp), %r13                 # 8-byte Reload
	movq	-64(%rbp), %r14                 # 8-byte Reload
	cmpl	-132(%rbp), %ebx                # 4-byte Folded Reload
	jl	.LBB2_18
	jmp	.LBB2_22
	.p2align	4, 0x90
.LBB2_20:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.start.if
                                        #   in Loop: Header=BB2_18 Depth=3
	callq	__check_bounds__@PLT
	movl	-96(%rbp), %ebx                 # 4-byte Reload
	movl	%ebx, %edi
	movq	-72(%rbp), %r13                 # 8-byte Reload
	movl	%r13d, %esi
	callq	__check_bounds__@PLT
	movq	-64(%rbp), %r14                 # 8-byte Reload
	movq	-184(%rbp), %rax                # 8-byte Reload
	movl	(%r14,%rax,4), %eax
	movq	-48(%rbp), %rcx                 # 8-byte Reload
	movl	%eax, -4184(%rbp,%rcx,4)
	incl	%ebx
	incl	%r15d
	cmpl	-132(%rbp), %ebx                # 4-byte Folded Reload
	jge	.LBB2_22
.LBB2_18:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.cond
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_3 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	cmpl	-128(%rbp), %r12d               # 4-byte Folded Reload
	jge	.LBB2_22
# %bb.19:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.start
                                        #   in Loop: Header=BB2_18 Depth=3
	movl	%ebx, %edi
	movl	%r13d, %esi
	callq	__check_bounds__@PLT
	movslq	%ebx, %rax
	movl	%ebx, -96(%rbp)                 # 4-byte Spill
	movq	%rax, -184(%rbp)                # 8-byte Spill
	movl	(%r14,%rax,4), %r14d
	movl	%r12d, %edi
	movq	-56(%rbp), %rsi                 # 8-byte Reload
                                        # kill: def $esi killed $esi killed $rsi
	callq	__check_bounds__@PLT
	movslq	%r12d, %rbx
	movq	-120(%rbp), %rax                # 8-byte Reload
	cmpl	(%rax,%rbx,4), %r14d
	movq	%rax, %r13
	movslq	%r15d, %rax
	movq	%rax, -48(%rbp)                 # 8-byte Spill
	movl	%r15d, %edi
	movl	$1000, %esi                     # imm = 0x3E8
	jle	.LBB2_20
# %bb.21:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.start.else
                                        #   in Loop: Header=BB2_18 Depth=3
	callq	__check_bounds__@PLT
	movl	%r12d, %edi
	movq	-56(%rbp), %rsi                 # 8-byte Reload
                                        # kill: def $esi killed $esi killed $rsi
	callq	__check_bounds__@PLT
	movl	(%r13,%rbx,4), %eax
	movq	-48(%rbp), %rcx                 # 8-byte Reload
	movl	%eax, -4184(%rbp,%rcx,4)
	incl	%r12d
	incl	%r15d
	movq	-72(%rbp), %r13                 # 8-byte Reload
	movq	-64(%rbp), %r14                 # 8-byte Reload
	movl	-96(%rbp), %ebx                 # 4-byte Reload
	cmpl	-132(%rbp), %ebx                # 4-byte Folded Reload
	jl	.LBB2_18
.LBB2_22:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.end
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	-112(%rbp), %rcx                # 8-byte Reload
	movl	%ebx, (%rcx)
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movl	%r12d, (%rax)
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movl	%r15d, (%rax)
	movq	-144(%rbp), %rax                # 8-byte Reload
	movl	(%rax), %r14d
	movslq	(%rcx), %rbx
	movq	-120(%rbp), %r13                # 8-byte Reload
	cmpl	%r14d, %ebx
	jge	.LBB2_25
	.p2align	4, 0x90
.LBB2_24:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.end.while.start
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_3 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movl	%r15d, %edi
	movl	$1000, %esi                     # imm = 0x3E8
	callq	__check_bounds__@PLT
	movslq	%r15d, %r12
	movl	%ebx, %edi
	movq	-72(%rbp), %rsi                 # 8-byte Reload
                                        # kill: def $esi killed $esi killed $rsi
	callq	__check_bounds__@PLT
	movq	-64(%rbp), %rax                 # 8-byte Reload
	movl	(%rax,%rbx,4), %eax
	movl	%eax, -4184(%rbp,%r12,4)
	incl	%r15d
	incq	%rbx
	cmpl	%r14d, %ebx
	jl	.LBB2_24
.LBB2_25:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.end.while.end
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	-112(%rbp), %rax                # 8-byte Reload
	movl	%ebx, (%rax)
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movl	%r15d, (%rax)
	movq	-104(%rbp), %rax                # 8-byte Reload
	movl	(%rax), %r14d
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movslq	(%rax), %rbx
	cmpl	%r14d, %ebx
	jge	.LBB2_28
	.p2align	4, 0x90
.LBB2_27:                               # %entry.while.start.while.start.endif.endif.while.end.while.end.while.end.while.end.while.start
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_3 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movl	%r15d, %edi
	movl	$1000, %esi                     # imm = 0x3E8
	callq	__check_bounds__@PLT
	movslq	%r15d, %r12
	movl	%ebx, %edi
	movq	-56(%rbp), %rsi                 # 8-byte Reload
                                        # kill: def $esi killed $esi killed $rsi
	callq	__check_bounds__@PLT
	movl	(%r13,%rbx,4), %eax
	movl	%eax, -4184(%rbp,%r12,4)
	incl	%r15d
	incq	%rbx
	cmpl	%r14d, %ebx
	jl	.LBB2_27
	jmp	.LBB2_28
.LBB2_29:                               # %entry.while.end
	movq	%rsp, %rbx
	leaq	-16(%rbx), %rsp
	callq	get_time@PLT
	movl	%eax, -16(%rbx)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movl	-16(%rbx), %esi
	subl	-124(%rbp), %esi                # 4-byte Folded Reload
	movq	__unnamed_2@GOTPCREL(%rip), %rdi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.type	__unnamed_1,@object             # @0
	.section	.rodata.str1.16,"aMS",@progbits,1
	.weak	__unnamed_1
	.p2align	4
__unnamed_1:
	.asciz	"error: memory violation\n"
	.size	__unnamed_1, 25

	.type	__unnamed_2,@object             # @1
	.section	.rodata.str1.1,"aMS",@progbits,1
	.weak	__unnamed_2
__unnamed_2:
	.asciz	"%d\n"
	.size	__unnamed_2, 4

	.section	".note.GNU-stack","",@progbits
