inherit NPC;
#include <ansi.h>
#define	BOOKNUM		4
#define	SHELFNUM	7
#define	RETRY		7

int ask_question();
int ask_rule();
int do_guess(string arg);
int do_list(string arg);

void create()
{
	set_name("������", ({ "liu haoyi", "liu" }));
	set("nickname", HIC"��Ϯ�Ӿ�"NOR);

	set("gender", "����");
	set("age", 40);
	set("long", "��Ŀ�⾼�����������أ������书���͡�\n");
set("age", 43);
  set("str", 30);
  set("per", 26);
  set("int", 30);
  set("cor", 50);
  set("cps", 50);
  set("combat_exp", 8200000);
  set_skill("literate", 300);
  set_skill("spear", 120);
  set_skill("force", 120);
  set_skill("dodge", 580);
  set_skill("parry", 550);
  set_skill("yanxing-steps", 550);
  set_skill("bawang-qiang", 500);
  set_skill("lengquan-force", 520);
  set_skill("unarmed", 560);
  set_skill("changquan", 520);
  map_skill("force", "lengquan-force");
  map_skill("unarmed", "changquan");
  map_skill("spear", "bawang-qiang");
  map_skill("archery", "xuanyuan-archery");
  map_skill("parry", "bawang-qiang");
  map_skill("dodge", "yanxing-steps");
  set("max_sen", 8800);
  set("max_kee", 8400);
  set("force", 9000);
  set("max_force", 4800);
  set("force_factor", 300);
  create_family("������", 4, "����");
  set("chat_chance_combat", 60);
  set("chat_msg_combat", ({
		(: perform_action, "unarmed", "zhiqi" :),
  }) );
	set_temp("apply/damage", 500);
        set_temp("apply/attack", 500);
	set_temp("apply/defense", 500);
	set_temp("apply/armor", 550);
	set("attitude", "peaceful");
	
	set("inquiry", ([
		"��" : (: ask_question :),
		"question" : (: ask_question :),
		"����" : (: ask_rule :),
		"rule" : (: ask_rule :),
	]) );

	setup();
	carry_object("/d/obj/cloth/linen")->wear();
}

void init()
{
        add_action("do_guess", ({"guess", "cai"}));
        add_action("do_list", ({"list", "lie"}));
	::init();
}

int ask_question()
{
	object me = this_player();
	int i, j, temp;
	string tempstr, result = "";

	
	if (uptime() - me->query_temp("last_question_time")< 60 )
           {
            message_vision("$N��$nҡ��ҡͷ��˵������̫���Խ������Ϣһ�°ɡ�\n",this_object(),me);
            return 1; 
          }
	
      if (me->query_temp("qipu_guess_win"))
		write("������Ц�����������ٽ�һ�Σ��ðɣ�����׼���þ����°ɡ���\n");
	else
	        write("�����ĴҴ��߽��鷿����һ���ֳ����ˡ�\n");
		write("�����ĵ�������Ŀ�������ģ�"+HIC"����һ��" + CHINESE_D->chinese_number(BOOKNUM) + "�ᡶ÷���ס������鷿����\n");
		write(CHINESE_D->chinese_number(SHELFNUM) + "����ܣ������Ұ���" + CHINESE_D->chinese_number(BOOKNUM) + "����ֱ�ŵ���ͬ�������ȥ����ֻ��³�\n");
		write("��ÿ��������Ǹ�����ϼ��ɡ���\n"NOR);
		write("�����ĵ��ͷ���������ˣ���"+HIC"��(guess)"+NOR"�ɣ�Ҳ����������"+HIC"����(rule)"+NOR"����\n");
	for (i = 0; i < BOOKNUM; i++) {
		temp = random(SHELFNUM) + 1;
		tempstr = "" + temp;
		for (j = 0; j < i; j++) {
			if (tempstr == result[j..j]) {
				temp = random(SHELFNUM) + 1;
				tempstr = "" + temp;
				j = -1;
			}
		}
		result += tempstr;
	}
	me->delete_temp("qipu_guess");
	me->set_temp("qipu_guess/result", result);
        me->set_temp("last_question_time",uptime());
	return 1;
}

int ask_rule()
{
	write("�����ĵ���������ܼ򵥣���ÿ����guess��������Ϊ�Ľ������\n");
	write("�����ĵ��������磬����Ϊ��һ���ڣ��ż��ϣ������ڣ��ţ������ڣ��ţ��Ĳ��ڣ��ţ��Ǿ�guess 2175����\n");
	write("�����ĵ������һ������ȫ�ԣ�ָ�¶����ĸ���ܷ����Ĳ�ģ�����ܶԣ�ָֻ�¶��ĸ���ܷ����û�в¶Էŵ����Ĳ�ģ��ĸ�������\n");
	write("�����ĵ�������������������ҷŵ�˳����һ���ڣ��ż��ϣ������ڣ��ţ������ڣ��ţ��Ĳ��ڣ��ţ���ô��Ӧ����1574����\n");
	write("�����ĵ�������¶ԣ��ż��������ᣬ��ʾ����һ��ȫ�ԣ�������¶ԣ��źͣ��ż������飬����û�¶����Ĳᣬ��ʾ���ж�����ܶԡ���\n");
	write("�����ĵ����������˰ɣ������˾Ϳ�ʼ��(guess)�ɡ���\n");
	write("�����ĵ�������ס����" + CHINESE_D->chinese_number(RETRY) + "�λ��ᡣ�������������ǰ�µĽ������ʱ������list���鿴�ġ���\n");
	return 1;
}

string justify_result(string result, string guess)
{
	int i, j, temp, very_right = 0, right = 0;

	for (i = 0; i < BOOKNUM; i++) {
		for (j = 0; j < BOOKNUM; j++) {
			if (guess[i..i] == result[j..j]) {
				if (i == j) very_right++;
				else right++;
			}
		}
	}
	return "ȫ�Ե���" + CHINESE_D->chinese_number(very_right) + "����ֻ����ܶԵ���" + CHINESE_D->chinese_number(right) + "����\n";
}

int do_guess(string arg)
{
	object me = this_player();
	int i, j, times,pot,lite;
	string result, tempstr1, tempstr2;

	if (!(result = me->query_temp("qipu_guess/result"))) return 0;
	if (!arg) return notify_fail("��Ҫ��ʲô���Ľ����\n");
	if (strlen(arg) != BOOKNUM) return notify_fail("���Ǹ�����ֻ��" + CHINESE_D->chinese_number(BOOKNUM) + "������\n");
	for (i = 1; i < BOOKNUM; i++)
		for (j = 0; j < i; j++)
			if (arg[i..i] == arg[j..j])
				return notify_fail("���Ǹ�����ÿ���鶼���ڲ�ͬ����������𣿣�\n");
	me->add_temp("qipu_guess/times", 1);
	times = me->query_temp("qipu_guess/times");
	if (arg == result) {
		if (times < 5) {
			tempstr1 = HIC"�����Ŀ����㣬���ȵص������������ֻ����";
			tempstr2 = "��";
		}
		else if (times < RETRY) {
			tempstr1 = HIC"�����ĵ�ͷ������������ֻ����";
			tempstr2 = "��";
		}
		else {
			tempstr1 = HIC"�����ĵ�������ܽ���ѽ��������";
			tempstr2 = "��";
		}
		write(tempstr1 + CHINESE_D->chinese_number(times) + "�λ���" + tempstr2 + "�³����ˡ���\n"NOR);
		me->delete_temp("qipu_guess");
		me->set_temp("qipu_guess_win", 1);
		pot = (RETRY - times+1)*me->query_kar()*3+random((RETRY - times+1)*me->query_kar()*3);       
                lite = 3+random(6);
           	if(pot>0) 
                { 
                 write(HIC"�����Ķ��������˴�Ĵָ�������������С���\n"NOR);
                  write(HIC"��õ���"+ CHINESE_D->chinese_number(pot) + "�㾭�� \n"NOR);
                  write(HIC"��Ķ���ʶ�ֽ����� \n"NOR);
                  me->add("potential",pot);
                  me->improve_skill("literate",lite);
         
                 }
	          me->set_temp("last_question_time",uptime());
	}
	else {
		write("�����ĵ�������µ���" + arg + "��" + justify_result(result, arg));
		if (times < RETRY) {
			write("�����ĵ������㻹��" + CHINESE_D->chinese_number(RETRY - times) + "�λ��ᣡ��\n");
			me->set_temp("qipu_guess/guess" + times, arg);
		}
		else {
			write("������������˵��������汿��" + CHINESE_D->chinese_number(RETRY) + "�λ��ᶼû���У���Ӧ����" + result + "����\n");
			write("�����ĵ������´��ٲ°ɣ���\n");
			me->delete_temp("qipu_guess");
		        me->set_temp("last_question_time",uptime());
		}
	}
	return 1;
}

int do_list(string arg)
{
	object me = this_player();
	int i, times;
	string result;

	if (!(result = me->query_temp("qipu_guess/result"))) return 0;
	times = me->query_temp("qipu_guess/times");
	write("�����ĵ���������ǰ�µĽ�����£���\n");
	for (i = 1; i <= times; i++) {
		write("��" + CHINESE_D->chinese_number(i) + "�Σ���" + me->query_temp("qipu_guess/guess" + i) + "��" + justify_result(result, me->query_temp("qipu_guess/guess" + i)));
	}
	return 1;
}

void die ()
{
  
           set("eff_kee", 5000);
           set("eff_gin", 5000);
           set("eff_sen", 5000);
           set("kee", 5000);
           set("gin", 5000);
           set("sen", 5000);
           set("force", 5000);
           set("mana", 5000);
           return ;
}


void unconcious()
{
   die();
}

