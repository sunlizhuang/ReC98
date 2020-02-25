#ifndef ERROR_NOT_RESIDENT
# define ERROR_NOT_RESIDENT "�킽���A�܂����܂���悧"
#endif
#ifndef REMOVED
# define REMOVED "����Ȃ�A�܂�����炢����"
#endif
#ifndef INITIALIZED
# define INITIALIZED "����ł́A��낵�����肢���܂�"
#endif

int main(int argc, const unsigned char **argv)
{
	seg_t sgm;
#if GAME == 5
	int i;
	resident_t far *resident;
	char far *resident_bytes;
	const char *res_id = RES_ID;
#else
	const char *res_id = RES_ID;
	int i;
	char far *resident_bytes;
#endif

	sgm = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	dos_puts2("\n\n" LOGO "\n");
	graph_clear();
#ifdef RES_INIT_TOP
	RES_INIT_TOP;
#endif
	if(argc == 2) {
		#define arg1_is(capital, small) \
			(argv[1][0] == '-' || argv[1][0] == '/') \
			&& (argv[1][1] == (capital) || argv[1][1] == (small))
		if(arg1_is('R', 'r')) {
			if(!sgm) {
				dos_puts2(ERROR_NOT_RESIDENT "\n\n");
				return 1;
			}
			dos_free(sgm);
			dos_puts2(REMOVED "\n\n");
			return 0;
		} else if(arg1_is('D', 'd')) {
			debug = 1;
		} else {
			dos_puts2("����ȃI�v�V�����t�����Ă��A�����ł�����\n\n");
			sgm = sgm; /* optimization barrier #1 */
			return 1;
		}
	}
	if(sgm) {
		dos_puts2("�킽���A���łɂ��܂��悧\n\n");
		argv = argv; /* optimization barrier #2 */
		return 1;
	}
	sgm = resdata_create(res_id, RES_ID_STRLEN, RES_PARASIZE);
	if(!sgm) {
		dos_puts2("���܂���A�킽���̋��ꏊ���Ȃ��́I\n\n");
		optimization_barrier_3();
		return 1;
	}
	resident_bytes = (char far *)MK_FP(sgm, 0);
	dos_puts2(INITIALIZED "\n\n");
	for(i = (RES_ID_STRLEN + 1); i < sizeof(resident_t); i++) {
		resident_bytes[i] = 0;
	}
	RES_INIT_BOTTOM;
	return 0;
}