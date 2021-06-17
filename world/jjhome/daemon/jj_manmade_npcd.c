// BY emotion

inherit F_DBASE;
#define MANMADE_NPC "/jjhome/npc/manmade_npc"

string *surname = ({"��", "��", "��", "��", "��", "�", "��", "��", "��", "��",
                    "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
                    "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
                    "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
                    "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
                    "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
                    "��", "¬", "³", "½", "·", "��", "��", "��", "��", "÷",
                    "��", "Ī", "ĸ", "��", "��", "��", "ŷ", "��", "��", "��",
                    "��", "Ƥ", "��", "��", "Ǯ", "ǿ", "��", "��", "��", "��",
                    "��", "��", "ʢ", "ʩ", "ʯ", "ʱ", "ʷ", "˾ͽ", "��", "��",
                    "̷", "��", "��", "��", "��", "ͯ", "Ϳ", "��", "Σ", "Τ",
                    "��", "κ", "��", "��", "��", "��", "��", "��", "��", "��",
                    "ϯ", "��", "��", "л", "��", "��", "��", "��", "Ѧ", "��",
                    "��", "��", "Ҷ", "��", "��", "��", "��", "��", "��", "��",
                    "Ԫ", "Ԭ", "��", "��", "��", "ղ", "��", "��", "��", "֣",
                    "��", "��", "��", "��", "��", "ׯ", "׿"});

string *firstname = ({"��", "��", "��", "��", "��", "��", "�п�", "����", "�",
                      "����", "˼��", "��", "��ũ", "�˷�", "��ͨ", "����", "����",
                      "��Ӣ", "����", "��", "����", "��", "�", "��Ӣ", "����",
                      "��", "����", "����", "����", "��ɽ", "�շ�", "С��", "��ɩ",
                      "����", "����", "����", "��", "����", "����", "һ��", "����",
                      "��", "��", "����", "����", "����", "��ʤ", "��", "��", "��Ƽ",
                      "����", "����", "��ɽ", "ȵ", "С��", "����", "��", "�Һ�",
                      "����", "����", "��Ÿ", "��֮", "����", "��", "ͨ��", "��",
                      "��", "����", "����", "����", "¡", "����", "����", "�߲�",
                      "�ᶽ", "��", "�ɺ�", "����", "��С", "��־", "��־", "����",
                      "˫Ӣ", "֮��", "����", "͢��", "����", "�Ĳ�", "����", "����",
                      "��ͬ", "��", "����", "ϣ��"
                      "�ܼ�", "����", "����", "ʿ��", "Ԫ��", "ϣ��", "����", "����",
                      "����", "����", "�˷�", "��", "һ��", "����", "�", "�Ӱ�",
                      "����", "����", "�ٶ�", "Ԫ��", "ԫ", "��", "��ɽ", "����", "��",
                      "��", "�", "��", "��", "̹", "�˷�", "��ƽ", "Х��", "����", "��",
                      "��", "����", "��", "��", "��", "��˪", "��˼", "˪��", "����",
                      "��", "����", "��", "�׷�", "����", "���", "��", "���", "��ʯ",
                      "�ٴ�", "����", "����", "Ǭ", "����", "����", "�ϴ�", "ֹ��", "����",
                      "����", "�Ƴ�", "��֮", "��¶", "��", "��", "����", "����", "����",
                      "��", "����", "����", "��ˮ", "��ׯ", "����", "����", "����",
                      "׿��", "����", "��", "��", "ʤ", "��", "��", "����", "�Ǻ�",
                      "��", "����", "��ʤ", "���", "˫��", "ȫ��", "��ɽ", "��ɽ",
                      "��ɽ", "��", "����", "��", "����", "����", "��", "����", "��",
                      "��", "����", "���", "���", "����", "��", "����", "�Ĳ�",
                      "�", "��", "���", "��̩", "���", "����", "����", "��",
                      "�Ӿ�", "����", "����", "����", "��Ȫ", "�̻�", "����", "Զɽ",
                      "����", "��", "̹֮", "��˪", "˼��", "���� ", "ǧ��", "����",
                      "Ԫ", "Ľ��", "��", "��", "��", "��", "��", "��", "��",

                      });

string *locations = ({
						"/d/lingtai/jingtang", // fc yun yang
						"/d/lingtai/room",  // fc puti
						"/d/moon/change_room", // moon chang e
						"/d/moon/lotuspond",  // moon chi meng
						"/d/nanhai/chaoyindong",  // putuo guan yin
						"/d/southern/emei/daochang", // putuo pu xian
						"/d/death/cuiyun",  // hell di zang
						"/d/sea/inside3",   // sea ao guang
						"/d/qujing/wudidong/inner-tang", // wudidong yu shu
						"/d/qujing/wuzhuang/chengyun", // wzg zheng yuan
						"/d/qujing/kusong/huoyun", // hyd hong hai er
						"/d/shushan/dadian", // shushan jian sheng
						"/d/pansi/pubu", // pansi
						"/d/kunlun/yuxugong", // kunlun yuan shi tian zun
						"/d/12gong/toby2",			// checked
						"/d/death/gate",			// checked
						"/d/jz/xw-2",				// checked
						"/d/jjf/front_yard",		// checked
						"/d/gao/gate",				// checked
						"/d/southern/emei/jinding",	// checked
						"/d/eastway/guandao1",		// checked
						"/d/changan/fendui",    	// checked
						"/d/dntg/hgs/entrance",		// checked
						"/d/kunlun/xiaolu3",		// checked
						"/d/33tian/33tian",  		// checked
						"/d/kaifeng/tieta",			// checked
						"/d/moon/ontop2",			// checked
						"/d/lingtai/gate",			// checked
						"/d/nanhai/gate",			// checked
						"/d/city/center",			// checked
						"/d/dntg/sky/nantian",		// checked
						"/d/qujing/wuzhuang/gate",	// checked
						"/d/meishan/erlangwai",		// checked
						"/d/liandan/road1",			// checked
						"/d/shushan/road1",			// checked
						"/d/penglai/penglai",		// checked
						"/d/xueshan/binggu",		// checked
						"/d/qujing/baoxiang/bei1",	// checked
						"/d/qujing/pingding/ping1",	// checked
						"/d/qujing/pingding/yalong1",	// checked
						"/d/qujing/wuji/square",		// checked
						"/d/qujing/chechi/jieshi1",	// checked
						"/d/qujing/tongtian/hedong1",	// checked
						"/d/qujing/jindou/jindou1",	// checked
						"/d/qujing/nuerguo/towna1",	// checked
						"/d/qujing/dudi/dudi1",		// checked
						"/d/qujing/firemount/cuiyun1",	// checked
						"/d/qujing/jilei/jilei1",	// checked
						"/d/qujing/jisaiguo/east1",		// checked
						"/d/qujing/jingjiling/jingji1",	// checked
						"/d/qujing/xiaoxitian/simen",	// checked
						"/d/qujing/zhuzi/zhuzi1",		// checked
						"/d/qujing/qilin/yutai",		// checked
						"/d/qujing/pansi/ling1",		// checked
						"/d/qujing/liusha/riverside",	// checked
						"/d/qujing/heifeng/road4",		// checked
						"/d/qujing/yingjian/lakeside3",	// checked
						"/d/qujing/guanyin/shanmen",	// checked
						"/d/qujing/yunzhan/shanlu1",	// checked
						"/d/qujing/shuangcha/shanlu3",	// checked
						"/d/qujing/village/cunkou",		// checked
						"/d/qujing/huangfeng/dongkou",	// checked
						"/d/qujing/biqiu/jie1",			// checked
						"/d/qujing/biqiu/zhuang",		// checked
						"/d/qujing/wudidong/firemount-wudidong3",	// checked
						"/d/qujing/qinfa/jiedao1",		// checked
						"/d/qujing/yinwu/huangye1",		// checked
						"/d/qujing/fengxian/jiedao1",	// checked
						"/d/qujing/yuhua/xiaojie1",		// checked
						"/d/qujing/baotou/shanlu1",		// checked
						"/d/qujing/zhujie/shanlu11",	// checked
						"/d/qujing/jinping/xiaojie1",	// checked
						"/d/qujing/qinglong/shanjian",	// checked
						"/d/qujing/tianzhu/jiedao11",	// checked
						"/d/qujing/maoying/shanpo1",	// checked
						"/d/qujing/lingshan/dalu1",		// checked
					  });

int debug_meet = 0;
int debug_fight = 0;
int debug_kill = 0;
int debug_learn = 0;
int debug_drug = 0;
int debug_item = 0;
int debug_skip_npc = 0;

int rzr_id = 0;
int max_npcs = 14;

int get_max_npcs() {
	return max_npcs;
}

int set_max_npcs(int count) {
	max_npcs = count;
	return 1;
}

int get_next_rzr_id() {
	int id;
	id = rzr_id;
	rzr_id++;
	if ( rzr_id > 9999 )
		rzr_id = 1;
	return id;
}

int is_debug_meet() {
	return debug_meet;
}

int is_debug_fight() {
	return debug_fight;
}

int is_debug_kill() {
	return debug_kill;
}

int is_debug_learn() {
	return debug_learn;
}

int is_debug_drug() {
	return debug_drug;
}

int is_debug_item() {
	return debug_item;
}

int is_debug_skip_npc() {
	return debug_skip_npc;
}

int set_debug_meet(int flag) {
	debug_meet = flag;
	return 1;
}

int set_debug_fight(int flag) {
	debug_fight = flag;
	return 1;
}

int set_debug_kill(int flag) {
	debug_kill = flag;
	return 1;
}

int set_debug_learn(int flag) {
	debug_learn = flag;
	return 1;
}

int set_debug_drug(int flag) {
	debug_drug = flag;
	return 1;
}

int set_debug_item(int flag) {
	debug_item = flag;
	return 1;
}

int set_debug_skip_npc(int flag) {
	debug_skip_npc = flag;
	return 1;
}

void debug_msg( string msg ) {
	CHANNEL_D->do_channel(this_object(), "debug", msg );
}

void announce_msg( string msg ) {
	CHANNEL_D->do_channel(this_object(), "rzr", msg );
}

void load_rzrs() {
	string* rzr_files;
	int i, count;
	int max_id = 0;
	rzr_files = get_dir(DATA_DIR "npc/rzr/*.o");
	if (!rzr_files)
		return;
	destruct(new(MANMADE_NPC));  // important: to load the code
	count = 0;
	for ( i = 0; i < sizeof(rzr_files); i++ ) {
		int temp;
		object rzr;
		temp = sscanf(rzr_files[i], "rzr%d.o",rzr_id);  // must use the one defined for this class, can not use local variable
		if ( temp != 1 )
			continue;

		  // check if the rzr is already in system
		if ( find_living("rzr"+rzr_id) )
			continue;  // don't load rzr if it is already in the system

		rzr = new(MANMADE_NPC);  // this call will increase rzr_id by 1
		rzr->set("id", "rzr"+(rzr_id - 1));
		rzr->restore();
		rzr->set_name(rzr->query("name"), ({"rzr"+(rzr_id - 1), "rzr"}));
		rzr->set_manmade_npc_chats();
		rzr->move(locations[random(sizeof(locations))]);
		count++;
		if ( rzr_id > max_id ) max_id = rzr_id;
		if (count>=max_npcs)
			break;
	}
	rzr_id = max_id + 1;

}

int shuffle_npc(object ob) {
	int i, k, count;
	object *rzrs, *enemy_list;
	object rzr;
	rzrs = children(MANMADE_NPC);
	count = sizeof(rzrs);
	announce_msg("ϵͳ��ʼ���·���������");
	for ( i = 0; i < count; i++ ) {
		object env;
		rzr = rzrs[i];
		env = environment(rzr);
		if (env) {
			if ( env->query("rzr_no_shuffle") )
				continue;
			rzr->delete_temp("no_move");
			rzr->clear_condition();
			// rzr->save();
		    if( rzr->is_fighting() )  {
				rzr->remove_all_killer();
				message("vision", "\n"+rzr->name() +
				      "�������һԾ�����ֵ����������ղ������������������Ǻ�����ڣ�\n\n",environment(rzr), rzr);

	        }
		    rzr->return_home(locations[random(sizeof(locations))]);
		}
	}
	remove_call_out("shuffle_npc");
	call_out("shuffle_npc", 1800, this_object() );
	return 1;
}

int generate_npc(object ob) {
	int i, count, real_count;
	object *rzrs;
	rzrs = children(MANMADE_NPC);
	count = sizeof(rzrs);
	real_count = 0;
	for ( i = 0; i < count; i++ ) {
		if (environment(rzrs[i])) {
			real_count++;
			rzrs[i]->enable_heart_beat();
		}
	}
	if (real_count < max_npcs) {
		object env;
		object rzr;
		rzr = new(MANMADE_NPC);
		rzr->move(locations[random(sizeof(locations))]);
		tell_room(environment(rzr), rzr->query("name") + "(" + rzr->query("id")
						+ ") ��Ȼ������һ��������\n" );
		announce_msg( rzr->query("name") + "(" + rzr->query("id")
						+ ") ������[" + environment(rzr)->query("short") + "]" );
	}
	remove_call_out("generate_npc");
	call_out("generate_npc", 30, this_object() );
	return 1;
}

void destroy_all_npcs() {
	object *rzrs;
	object rzr;
	int i, count;
	object env;
	announce_msg("��Ϊ������������, ����ؾ�����ϵͳ�е����������˼�ʱ����");
	rzrs = children(MANMADE_NPC);
	count = sizeof(rzrs);
	for ( i = 0; i < count; i++ ) {
		rzr = rzrs[ i ];
		env = environment(rzr);
		if ( env ) {
			tell_room(env, "ֻ������һ�����粻ƫ���еػ��� " + rzr->query("name") + "(" + rzr->query("id")
						+ ") ����֮��Ϊһ�ѻҽ���\n" );
			rzr->die();
		}
	}

}

void create()
{
    seteuid(getuid());
    set("name", "������ϵͳ����");
    set("id", "manmaded");
    load_rzrs();
    call_out("shuffle_npc", 20, this_object() );
    call_out("generate_npc", 30, this_object() );
}

string generate_name() {
	return surname[ random( sizeof(surname) ) ] + firstname[ random( sizeof(firstname) ) ];
}
