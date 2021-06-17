#include <ansi.h>

inherit NPC;
string start();
int dn();
void end_game();
int compare_score(object ob1, object ob2);
string end_time();

object ob = this_object();
object *users = ({});
object *tUsers = ({});
object *ctUsers = ({});

void create()
{
  set_name(HIY"��������"NOR, ({ "daniao wangzi", "wangzi" }) );
  set("title",HIW"�ãӴ���������ʹ"NOR);
  set("gender", "����");
  set("age", 20);
  set("combat_exp", 300000+random(20000));
  set("attitude", "heroism");
  set("no_clean_up",1);
  set("str", 30);
  set("per", 30);
  set("max_kee", 600);
  set("max_gin", 600);
  set("force", 600);
  set("max_force", 600);
  set("force_factor", random(20)+25);
  set_skill("unarmed", 80);
  set_skill("parry", 80);
  set_skill("dodge", 80);
	set("inquiry", ([
		"����" : (: start :),
		"����" : (: start :),
		"game" : (: start :),
		"cs" : (: start :),
		"cslist" : (: dn :),
		"�μ���" : (: dn :),
		"�μ���" : (: dn :),
		]) );  
  setup();

  carry_object("/d/qujing/baoxiang/obj/changpao")->wear();
}

void init()
{
   add_action("do_baoming", "baoming");
   ::init();
}

/******************************************************************************
todo:
	��ʼ������
******************************************************************************/
string start()
{
	object me;
	me = this_player();
	if ( ob->query("start_baoming") ) return "�����Ѿ���ʼ������ָ��baoming�μ���Ϸ��\n";
	if ( ob->query("end_baoming") ) return "��α����Ѿ���ʼ������һ�ΰɣ�\n";
	if ( ob->query("no_baoming") ) return end_time();
	if ( me->query("daoxing") <= 500000 ) return "�����̫ǳ��ֻ���ټ����������ˡ�\n";
	if ( me->query("combat_exp") <= 500000 ) return "��ʵս����̫�٣�������ȥ��ĵط����������ɡ�\n";
	ob->set("start_baoming",1);
	message( "system", HIR"��"+HIY"��������"+HIR"���� "HIR+me->query("family/family_name")+HIY""+me->query("name")+HIR"ǰ�������·���ɲμӣãӴ���,Ը��μ�������������ڱ�����\n" NOR, users() );
          call_out("choose_faction",5*60);
  return "����ϵͳ�Ѿ����������������(baoming)�ɡ�\n";
}

/******************************************************************************
todo:
	�����߱�����
******************************************************************************/
int do_baoming()
{
	int i ;
	object me;
	me = this_player();

	if ( ob->query("end_baoming")) return notify_fail("��ΣãӴ����Ѿ�ֹͣ������\n");
	if ( !ob->query("start_baoming") ) return notify_fail("�ãӴ�����û��ʼ�����ء�\n");
if ( me->query_temp("no_heal_up/bian") ) return notify_fail("������ʱ���ǲ�Ҫ�����˰ɡ�\n");
	if ( me->query_temp("in_hell") ) return notify_fail("����ǲ��ܲμӱ����ġ�\n");
	if ( me->query("daoxing") <= 500000 ) return notify_fail("�����̫ǳ�����ǲ�Ҫ�μ��ˡ�\n");
	if ( me->query("combat_exp") <= 500000 ) return notify_fail("��ʵս����̫�٣�������ȥ��ĵط����������ɡ�\n");

	
	// �ж��Ƿ��ظ���������ͬip ͬport ����
	for ( i = 0; i < sizeof(users); i++ )
	{
		if ( users[i] == me ) return notify_fail("�㲻��������������\n");

//                if ( (users[i]->query_ip_number() == me->query_ip_number()) && (users[i]->query_ip_port() == me->query_ip_port()) )
//                       return notify_fail("�㲻��ͬʱ����������������id�μӱ�����\n");
	}
	
	// Add this new user
	users += ({ me });
	
	message( "chat", HIC"��"+HIY"��������"+HIC"���� "HIC+me->query("family/family_name")+HIY""+me->query("name")+HIC"�����μӣãӴ�����\n" NOR, users() );
	return 	1;
}

/******************************************************************************
todo:
	�������������
	�Ȱ�score������ѡ��(���Ѹ�Ϊ������飬���ٰ�score ����)
	������Ϊt���ݻ𷸣���ż����Ϊct����������
******************************************************************************/
void choose_faction()
{
	int i,j;
	object *list;
	string cslist;
	string lastType;

  list = ({});
	
	// ��������̫�٣�ȡ��������
	if ( sizeof(users)<2 ) {
		message( "system", HIR"��"+HIY"��������"+HIR"���� ���ڲ�����������ʮ�ˣ�����ȡ����\n" NOR, users() );
		users = ({});
	  tUsers = ({});
	  ctUsers = ({});
		end_game();
		return;
	}
	ob->set("end_baoming",1);
	
	// ����ÿ���˵���𣬲������䱾�ˡ�
  
  
  /*******************************************************************
 
  for ( i = 0; i < sizeof(users); i++ )
  {
  	j = random(sizeof(users)-i);
		message( "system", HIR"��"+HIY"��������"+HIR"����"+users[i]->query("id")+users[j]->query("id")+" \n" NOR, users() );
  	list += ({users[j]});
  	users[j] = users[sizeof(users)-i];       // ��һ�������⡣����������������������������
  }
  ���ϲ���Ϊ���ĺ�������鷽ʽ��
  *******************************************************************/
  // ��score ����,Ϊ�˷�ֹ������ô˷��鷽ʽȡ�ý����ĳ������������
  list = sort_array(users, (: compare_score :) );      
  users = list;
	for ( i = 0; i < sizeof(users); i++ )
	{
		string type;
		type = i%2 ? (lastType == "t" ? "ct" : "t") : (random(2) ? "t" : "ct");
		lastType = type;
		users[i]->set_temp("pkgame", type);
		message( "tell", HIR"��" + HIY"��������" + HIR"���� �����ڿ�ʼ����"BLINK HIY + 
			(type == "t" ? "�ݻ�" : "����") +
			HIR"��\n" NOR, users[i] );
		if (type == "t")
			tUsers += ({ users[i] });
		else
			ctUsers += ({ users[i] });
	}

/*
	// �����Ա����
	cslist = HIR"��"+HIY"��������"+HIR"���� ϵͳchoose�����\n" NOR;
	cslist += "�ݻ��飺";
	for ( i = 0; i < sizeof(users); i+=2 )
	{
		cslist += users[i]->query("name") + "	";
	}
	cslist += "\n";
	cslist += "�����飺";
	for ( i = 1; i < sizeof(users); i+=2 )
	{
		cslist += users[i]->query("name") + "	";
	}
	cslist += "\n";
	message( "system", cslist, users() );
*/	
	users = ({});
	tUsers = ({});
	ctUsers = ({});
	message( "system", HIR"\n\n��"+HIY"��������"+HIR"���� CS������ʽ��ʼ��\n\n" NOR, users() );
	ob->set("no_baoming",1);
	ob->delete("start_baoming");	
	call_out("wait_start",3);
	return;
}

void wait_start()
{
	"/cmds/usr/pkgame"->main(0,"start");
}
/******************************************************************************
todo:
	User��score����ص�������
******************************************************************************/
int compare_score(object ob1, object ob2)
{
    int score1,score2;

    score1 = "/cmds/usr/top"->get_score(ob1);
    score2 = "/cmds/usr/top"->get_score(ob2);

    return score2 - score1;
}

/******************************************************************************
todo:
	���ز�����������
******************************************************************************/
int dn()
{
	int i;
	write("�����ߣ�\n");
	for ( i = 0; i < sizeof(users); i++ )
	{
		write(users[i]->query("name")+"	");
	}
	write("\n");
	return 1;
}		
	
/******************************************************************************
todo:
	cs��Ϸ����������ڲ�������
******************************************************************************/
void end_game() {
	children("/u/take/cs")->delete("end_baoming");
	children("/u/take/cs")->delete("start_baoming");	
	call_out("restart",180*60);
}

void restart()
{
	children("/u/take/cs")->delete("no_baoming");
}

string end_time()
{
	string cStatus ;
	cStatus = chinese_number ( 180 - ( time() - ob->query("End_Time") )/ 60  ) ;
	if ( !cStatus ) return "�ã�ϵͳ�����������⣬��֪ͨ"+BLINK HIY"����(take)��\n"NOR;
	cStatus = "�����ս��������"BLINK HIY+cStatus+NOR"���������ɡ�\n";
	return cStatus;
}
