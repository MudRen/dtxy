// д�˺þ�  by take
#include <skill.h>
#include <ansi.h>


inherit NPC;
inherit F_MASTER;

string expell_me(object me);
int donghai_quest(object who);
string ask_mieyao();
string ask_cancel();
int begin_go();
int begin_yuanshoucheng();


void create()
{
       	set_name("����", ({"ao guang", "ao","guang","longwang","wang"}));

	set("long","�����Ƕ��������������ֱֵܷ��ƹܶ��������ϣ����ĺ���
������ˮ���ڶ࣬���ƺƴ�ٲȻ����һ����\n");
       set("gender", "����");
       set("age", 66);
	set("title", "��������");
	set("class","dragon");
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("combat_exp", 1260000);
       set("daoxing", 1500000);
       set("rank_info/respect", "����");
       set("per", 20);
       set("str", 30);
       set("max_kee", 3000);
       set("max_gin", 400);
       set("max_sen", 1500);
       set("force", 3000);
       set("max_force", 1500);
       set("force_factor", 120);
       set("max_mana", 800);
       set("mana", 1600);
       set("mana_factor", 40);
       set("combat_exp", 1200000);
       set("daoxing", 1500000);
       set_skill("huntian-hammer", 200);
	set_skill("hammer", 200);
	set_skill("literate", 150);
       set_skill("unarmed", 200);
       set_skill("dodge", 200);
       set_skill("force", 200);
       set_skill("parry", 200);
       set_skill("fork", 200);
       set_skill("spells", 200);
	set_skill("seashentong", 200);
	set_skill("dragonfight", 200);
	set_skill("dragonforce", 200);
	set_skill("fengbo-cha", 200);
	set_skill("dragonstep", 200);
	map_skill("hammer", "huntian-hammer");
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("dodge", "dragonstep");
       set("chat_chance_combat", 50);
       set("chat_msg_combat", ({
                (: cast_spell, "hufa" :),
                (: perform_action, "unarmed", "sheshen" :),

                }) );
             set("inquiry", ([ 
           "��̨����": (: begin_go :),
           "����": (: begin_yuanshoucheng :),
           "�빬": (: expell_me :),
	   "leave": (: expell_me :), 
           "����": (: ask_mieyao :),
           "cancel": (: ask_cancel :),
           "����": (: donghai_quest :),
           "weapon": (: donghai_quest :), 
        ]) );

        create_family("��������", 1, "ˮ��");
	set_temp("apply/armor",50);
	set_temp("apply/damage",25);
	setup();

        carry_object("/d/sea/obj/longpao")->wear();
}
void init()
{
	::init();
	add_action("do_agree", "agree");
	add_action("do_learn", "xuexi");
}


void destroy(object ob)
{
        destruct(ob);
        return;
}

void unsetlearn(object ob)
{
	if (find_player(ob->query("id"))) {
		ob->set_temp("temp/learn", 0);
		ob->save();
		}
}


string *reject_msg = ({
	"˵������̫�����ˣ�����ô�ҵ���\n",
	"�����ܳ�����һ����˵������̣�����ô�ҵ���\n",
	"Ц��˵��������Ц�ˣ��������С�������ʸ�ָ�㡹��ʲô��\n",
});

int do_learn(string arg)
{
	string skill, teacher, master;
	object me= this_player(), ob;
	int master_skill, my_skill, sen_cost;

	if(!arg || sscanf(arg, "%s from %s", skill, teacher)!=2 )
		return notify_fail("ָ���ʽ��xuexi <����> from <ĳ��>\n");

	if( me->is_fighting() )
		return notify_fail("����ĥǹ������������\n");

	if( !(ob = present(teacher, environment(me))) || !ob->is_character())
		return notify_fail("��Ҫ��˭��̣�\n");

	if( !living(ob) )
		return notify_fail("�ţ���������Ȱ�" + ob->name() + "Ū����˵��\n");

	if( !master_skill = ob->query_skill(skill, 1) )
		return notify_fail("���������±����ұ���ѧ�ˡ�\n");

	if (skill != "unarmed" || !me->query_temp("temp/learn") ) 
		return notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );

	notify_fail(ob->name() + "��Ը���������ܡ�\n");
	if( ob->prevent_learn(me, skill) )
		return 0;

	my_skill = me->query_skill(skill, 1);
	if( my_skill >= master_skill )
		return notify_fail("�������ĳ̶��Ѿ�������ʦ���ˡ�\n");

	notify_fail("����Ŀǰ��������û�а취ѧϰ���ּ��ܡ�\n");
	if( !SKILL_D(skill)->valid_learn(me) ) return 0;

	sen_cost = 250 / (int)me->query_int();

	if( !my_skill ) {
		sen_cost *= 2;
		me->set_skill(skill,0);
	}

	if( (int)me->query("learned_points") >= (int)me->query("potential") )
		return notify_fail("���Ǳ���Ѿ����ӵ������ˣ�û�а취�ٳɳ��ˡ�\n");
	printf("����%s���йء?s������ʡ�\n", ob->name(),
		to_chinese(skill));

	if( ob->query("env/no_teach") )
		return notify_fail("����" + ob->name() + "���ڲ���׼���ش�������⡣\n");

	tell_object(ob, sprintf("%s�������йء?s������⡣\n",
		me->name(), to_chinese(skill)));

	if( (int)ob->query("sen") > sen_cost/5 + 1 ) {
		if( userp(ob) ) ob->receive_damage("sen", sen_cost/5 + 1);
	} else {
		write("����" + ob->name() + "��Ȼ̫���ˣ�û�а취����ʲô��\n");
		tell_object(ob, "������̫���ˣ�û�а취��" + me->name() + "��\n");
		return 1;
	}
		

	if( (int)me->query("sen") > sen_cost ) {
		if( (string)SKILL_D(skill)->type()=="martial"
		&&	my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) {
			printf("Ҳ���ǵ��в��������%sĻش������޷���ᡣ\n", ob->name() );
		} else {
			printf("������%s�ָ�����ƺ���Щ�ĵá�\n", ob->name());
			me->add("learned_points", 1);
			me->improve_skill(skill, random(me->query_int()));
		}
	} else {
		sen_cost = me->query("sen");
		write("�����̫���ˣ����ʲôҲû��ѧ����\n");
	}

	me->receive_damage("sen", sen_cost );

	return 1;
}

void attempt_apprentice(object ob)
{	
	if( (int)ob->query_skill("dragonforce",1) < 50
	|| (int)ob->query_skill("seashentong", 1) < 50) {
	command("say " + RANK_D->query_respect(ob) +
		"�����ȵ��󽫾���СŮ���ѻ������������������ɡ�\n");
	return;
	}	
        command("smile");
        command("say �ѵ�" + RANK_D->query_respect(ob) +
		"�д���־�������պ���Ŭ����Ϊ�Ҷ����������⡣\n");
        command("recruit " + ob->query("id") );
	return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "dragon");
}

string expell_me(object me)
{
  me=this_player();
  if((string)me->query("family/family_name")=="��������")
    {
      me->set_temp("betray", "lg");
      command("sigh");
      return ("��Ҫ�뿪��Ҳ����ǿ����ֻ�ǰ��Ҷ�����أ�ȴ���ܷ���
���¼���������࣬�������ķ��벩����������ǰ����ת�����Ը��(agree)?\n");
    }
  return ("ȥ����Ԭ�����ɣ�������֪����\n");
}

int do_agree(string arg)
{
  object me;
  me = this_player();
  if(me->query_temp("betray")=="lg")
    {
      message_vision("$N���������Ը�⡣\n\n", me);
      command("say �˸���־������" + RANK_D->query_respect(me) +
        "��Ը���ڶ������������ȥ�ɡ�ֻ�ǽ����ն�" + RANK_D->query_respect(me) +
	"������Ϊ֮������\n");
      me->set_skill("dragonforce", (int)me->query_skill("dragonforce",1)/2);
      me->set_skill("dragonfight", (int)me->query_skill("dragonfight",1)/3);
this_player()->set("combat_exp",this_player()->query("combat_exp")/5*4);
this_player()->set("daoxing",this_player()->query("daoxing")/5*4);
      me->delete("family");
      me->delete("class");
      me->set("title", "��ͨ����");
      me->set_temp("betray", 0);
      me->add("betray/count", 1);
      me->add("betray/longgong", 1);
      me->save();
      return 1;
    }
  return 0;
}

int donghai_quest(object who)
{
  object me=this_object();
  object fighter;
  string weapon_name,weapon_id,weapon_unit,temp_flag;

  who=this_player();
  if (who->query("dntg/donghai")=="done") {
    message_vision("$N��ɫ�ҵ�������Ը��˵��������������ϵط���������������\n",this_object());
    call_out("sendto_maze",2,who);
    return 1;
  }

  if (
      who->query("dntg/donghai") == "begin"
      || who->query("dntg/donghai") == "da kan dao"
      || who->query("dntg/donghai") == "jiu gu cha"
      || who->query("dntg/donghai") == "mei hua chui"
     )

    {
        if (who->query("dntg/donghai") == "begin")
           {weapon_name="�󿳵�"; weapon_id="da kan dao";weapon_unit="��";temp_flag="try_dao";}
        if (who->query("dntg/donghai") == "da kan dao")
           {weapon_name="�Źɲ�"; weapon_id="jiu gu cha";weapon_unit="֧";temp_flag="try_cha";}
        if (who->query("dntg/donghai") == "jiu gu cha")
           {weapon_name="÷����"; weapon_id="mei hua chui";weapon_unit="��";temp_flag="try_chui";}
        if (who->query("dntg/donghai") == "mei hua chui")
           {weapon_name="�����"; weapon_id="hua gan ji";weapon_unit="��";temp_flag="try_ji";}

        
        if (present(weapon_id, this_player()) && present("ye cha", environment()))
          message_vision("����������������"+weapon_name+"��ҹ�������ɣ�\n",me);
        else if (present(weapon_id, environment()) && present("ye cha", environment()))
          message_vision("����������������"+weapon_name+"��ҹ�������ɣ�\n",me);
        else if (present(weapon_id, this_player()) || present(weapon_id, environment()))
          {
          message_vision("��������˵���������Ҹ���������������\n",me);
          message_vision("��������һ���֣�һ��ҹ�����˹�����\n",me);
          fighter = new ("/d/dntg/donghai/npc/fighter");
          fighter->move(environment(me));
          } 
        else if (present("ye cha", environment()))
          message_vision("����������֪��"+weapon_name+"��˭��ȥ�ˣ�\n",me);
        else
          {
          message_vision("$N��æ����˵����"+RANK_D->query_respect(who)+"�Ժ�������룿\n",me,who);
          message_vision("������������"+weapon_unit+weapon_name+"���պ�����ʹ��"+RANK_D->query_respect(who)+"����������������"+RANK_D->query_respect(who)+"�ðɣ�\n",who);
          who->set_temp("dntg/donghai",temp_flag);
          call_out ("fight_quest",2,who);
          }
        return 1;
    } 

  else if (who->query("dntg/donghai") == "hua gan ji" )
    {
    me->command("consider");
    message_vision("�Ӻ�����һ�����ţ�����������С��˵�˼��仰��\n",me);
    call_out ("sendto_maze",3,who);
    return 1;
    }
   command("nod");
  message_vision("$N�������˵����Ҫ���������������е��ǣ�ȥ����ŪЩ�ɡ���\n",me);
  message_vision("$N���˶٣���˵�����������ı�������������Щ��������Ҳʹ���ˡ���\n",me);
  command("wave");
  return 1;
}

void fight_quest (object who)
{
  object me=this_object();
  object fighter,fa_bao;
  string weapon_name,weapon_id,weapon_unit;


  if (who->query("dntg/donghai") == "begin")
    {weapon_name="�󿳵�"; fa_bao = new ("/d/dntg/donghai/obj/dakandao");weapon_unit="��";}
  if (who->query("dntg/donghai") == "da kan dao")
    {weapon_name="�Źɲ�"; fa_bao = new ("/d/dntg/donghai/obj/jiugucha");weapon_unit="֧";}
  if (who->query("dntg/donghai") == "jiu gu cha")
    {weapon_name="÷����"; fa_bao = new ("/d/dntg/donghai/obj/meihuachui");weapon_unit="��";}
  if (who->query("dntg/donghai") == "mei hua chui")
    {weapon_name="�����"; fa_bao = new ("/d/dntg/donghai/obj/huaganji");weapon_unit="��";}

  message_vision("��������һ���֣�һ��ҹ��̧��һ"+weapon_unit+weapon_name+"��\n",me);
  fighter = new ("/d/dntg/donghai/npc/fighter");
  fighter->move(environment(me));
  fa_bao->move(environment(me));
  message_vision("��������˵������Ҫ��Ҫ���ҵ���������������\n",me);
}

void sendto_maze (object who)
{
  object me=this_object();
  message_vision("$N˵����"+RANK_D->query_respect(who)+"�书�������ɵ�����ĺ�������һ�Զ�����������\n",me,who);
  call_out ("send_maze",3,who);
}

void send_maze (object who)
{
  object me=this_object();
  message_vision("˵�ţ�����������$N�͵���һ���ط���\n",who);
  who->move("/d/dntg/donghai/haidimigong");
  message_vision("$Nһ���ֵ���"+RANK_D->query_respect(who)+"��ǰ�߼��ɿ�����������ˡ�Ϸ򲻷����ˡ�\n",me,who);
  message_vision("˵�գ�����ת��ع��ˡ�\n",me);
}
string ask_cancel()
{
    object me=this_player();
if((int)me->query_temp("m_mieyao"))
{
      me->add("daoxing",-2000);
      me->delete_temp("m_mieyao");
      me->delete("secmieyao");
      me->delete("secmieyao/type");
      me->delete("secmieyao/location");
      me->delete("secmieyao/place");
      me->delete("secmieyao/name");
      me->delete("secmieyao/id");
     return ("û�õĶ�����");
}
else
{
     return ("���������𣿣�");
}
}
string ask_mieyao()
{
   object me=this_player();
  if(me->query("class")!="dragon")return "�㲻�Ǳ������ˣ�";
   tell_room(environment(me),"������ͷ�����롣\n");
   return "/d/obj/mieyao"->query_yao(me);
}

void move_lingtai(object me)
{
    message_vision(HIW"\n\n\n����ʱ����������̨��Ժ.\n\n"NOR,me);

    me->move("/d/lingtai/inside1");
}
		
int begin_go()
{
	object me,ob;
   	int dx,dx1,wx,qn;
    me=this_player();
	ob=this_object();
	dx=(me->query("daoxing"))/20;
if (dx>=100000) dx=100000;
	dx1=dx/1000;
	wx=(me->query("combat_exp"))/20;
if (wx>=10000) wx=10000;
	qn=30000;
    if (!me->query("fangcun/panlong_visite"))
	  return 0;
    if (me->query("guanli/longgong"))
	  return 0;

		if (me->query("fangcun/panlong_longgong")=="done")
	{
        message_vision("\n���㹧�����" + RANK_D->query_respect(me) + "���ؼ���,������Ͷ���ɣ�\n"NOR,me);
        message_vision(HIC"\nֻ������ŵͷ�����һ�ɾ���,����$N�Ͱ��㾶ֱ����̨�����ȥ��\n"NOR,me);
		me->start_busy(2);
    	ob->move("/d/lingtai/inside1");
		call_out("move_lingtai",3,me);
		return 1;
	}

    if ((me->query_temp("fangcun/panlong_longgong_longzhu")=="done")&&(me->query_temp("fangcun/panlong_longgong_yuanshoucheng")=="done"))
	{
		me->add("fangcun/panlong_visite",1);
		me->set("fangcun/panlong_longgong","done");
        me->delete_temp("fangcun/panlong_longgong_longzhu");
        me->delete_temp("fangcun/panlong_longgong_yuanshoucheng");
           message("chat",HIC+"��"+HIW+"��������"+HIC+"������(Ao guang)��"+me->query("name")+"�书��ǿ,��ʶ����,����֮������������ǰ�����أ�\n"NOR,users());
              message("chat",HIC+"��"+HIW+"��������"+HIC+"������(Ao guang)��"+me->query("name")+"�õ�����������"+chinese_number(dx1)+"�꣬��ѧ"+wx+"�㣬Ǳ��30000�㣮\n"NOR,users());
   	    if (me->query("family/family_name")=="����ɽ���Ƕ�")
    		message_vision("\n\n����������ջ���" + RANK_D->query_respect(me) + "����֪ͨ����һ��.\n"NOR,me);
		me->add("daoxing",dx);
		me->add("combat_exp",wx);
		me->add("potential",30000);
	    if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
			me->set("guanli/longgong",1);
		return 1;
	}

/*	if (me->query_temp("fangcun/panlong_longgong_longzhu")=="done")
	{
        message_vision("\n�������" + RANK_D->query_respect(me) + "��Ȼ�书��ǿ,��\n"NOR,me);
		return 1;
    }
*/ //        �㶨 yuanshoucheng ����
   			if (me->query_temp("fangcun/panlong_longgong_longzhu")=="done")
	{
              command("sigh");
    		  command("say ����δ�ˣ��������к������ȥ���ˣ�\n");
              command("shake");

			  return 1;
	}

			if ((me->query("fangcun/panlong_longgong")!="begin")&&(me->query("fangcun/panlong_visite")))
    {
  command("say Ŷ��ԭ��" + RANK_D->query_rude(me) + "ǰ����������������̨���񣬽���������һ���ǲ��ѣ�ֻ��
          ��֪��" + RANK_D->query_rude(me) + "�书��Σ�����" + RANK_D->query_rude(me) + "��սʤ�ҾŸ��������ĺ��������Ų���
	  ����������ұ��Ӧ�����һ�£�\n");
   me->set("fangcun/panlong_longgong","begin");
	return 1;
	}
  command("say ��ô��" + RANK_D->query_respect(me) + "���ҾŸ����Ӷ��򲻹���\n");
  command("haha ");

  return 1;
}

int accept_object(object me, object ob)
{
  string thing=(string)ob->query("id");

  if (me->query("fangcun/panlong_longgong")=="begin")
  {
           if ((ob->query("id") == "jiucai longzhu")&&(ob->query("name")=="�Ų�������")&&(me->query_temp("fangcun/panlong_longgong_longzhu")!="done"))
    {
      command ("ah "+ob->query("id"));
      me->set_temp("fangcun/panlong_longgong_longzhu","done");
//       call_out("destroy", 1, ob);
      message_vision("\n���㾪����û�뵽��" + RANK_D->query_respect(me) + "��Ȼ��һ���汾�죬ǰ��������ʧ���ˣ�����" + RANK_D->query_respect(me) + "Ī�֣�\n\n\n"NOR,me);
	  message_vision("����ͻȻʧȥ��һ����Ȼ����ɫ�������ݵ�˵����\n
	  ��Ȼ" + RANK_D->query_respect(me) + "ƾ����ȡ���˾Ų������鰴��˵������ҲӦ�ü�����" + RANK_D->query_respect(me) + "ȥ
��̨����ֻ������һ"+HIY"����"+NOR"δ�ˣ��Ҷ������������ټ���λ�ɼ�ͬ����\n\n"NOR,me);
	  return 1;
	}
	
 if ((me->query_temp("fangcun/panlong_longgong_yuanshoucheng")=="begin")&&(ob->query("id") == "yuan shoucheng")&&(ob->query("name")=="Ԭ�س�"))
	{
		  command ("great "+me->query("id"));
          me->set_temp("fangcun/panlong_longgong_yuanshoucheng","done");
      	  me->set("fangcun/panlong_nowaylonggong",1);
		  message_vision("�����ȵ������˰��������ţ�����ϵ����Ҵ�����Σ�\n\n"NOR,me);
		  return 1;
	}
 if ((me->query_temp("fangcun/panlong_longgong_yuanshoucheng")=="begin")&&(me->query_temp("help_yuan")=="yes")&&(ob->query("longgong_pass")==1))
	{
    if (!me->query_temp("no_heal_up/bian"))
{
				me->set_temp("fangcun/panlong_longgong_yuanshoucheng","done");
                message_vision("\n\n����˫�ֽӹ�"+HIY"��ּ"+NOR"��ϸϸ��������������\n\n",me);
				call_out("longgong_done1",2);
				return 1;
}
        if ((me->query_temp("apply/name")[0] == "��˶�")&&(me->query_temp("apply/id")[0]=="gui badou"))
			{
			  me->set_temp("fangcun/panlong_longgong_yuanshoucheng","done");
                me->add("fangcun/panlong_visite",1);
                message_vision("\n\n����˫�ֽӹ�"+HIY"��ּ"+NOR"��ϸϸ��������������\n\n",me);
				call_out("longgong_done",2);  
			  return 1;
			}
				
	}
  }

command ("say ����ʲô������");
return 1;
}

void longgong_done()
{
	object me;
	me=this_player();
    command ("say �⣮������ʦ����˼�ǣ�����������");
    message_vision(WHT"\n$N����˵�����������������������ͬΪ���壬�������������Υ�����ο���
��          ��������Ϊ��һʱ������һ����������һ���ʶ������Υּ����
	    ������Ϊ��֮���������β���˼�����У��в������ǧ�Ŷ�������
	    ������Ц��\n"NOR,me);
    message_vision("\n�����ͷ��˼������\n"NOR,me);
	call_out("longgong_done2",3,me);
}

void longgong_done2(object me)
{
    message_vision("\n��������ͷ��˼���ã�������̼亹�����£�\n\n"NOR,me);
    command ("say ��ʦȰ��Ķԣ�����Ҫɱ��������֮�ˣ��񲻱��������Ƿǲ��֣��ڰײ����ǧ�Ŷ�����");
    message_vision(WHT"\n\n$NͻȻ������һ�䣬������Ц��\n"NOR,me);
    message_vision("\n����Ծ����ѣ���������ָ��$N�ȵ����㣮���㾿���Ǻ��ˣ�\n"NOR,me);
	call_out("longgong_done3",3,me);
}

void longgong_done3(object me)
{
	me->delete_temp("spellslevel");
	me->delete_temp("apply/name");
	me->delete_temp("apply/id");
	me->delete_temp("apply/short");
	me->delete_temp("apply/long");
	me->delete_temp("family");
    me->delete_temp("no_heal_up/bian");
    me->delete_temp("d_mana");
	  while( environment(me)->is_character() )
	     me->move(environment(environment(me)));
          message_vision(HIY "\n\n$N�����������һ�Σ���������\n\n"
	    NOR,me);
    message_vision("\n����ŭ����ԭ���������" + RANK_D->query_rude(me) + "����Ϸˣ���ң�\n\n"NOR,me);
    message_vision(WHT"\n$N��æ��ȭ���������������ˣ��������ֻΪ��������������Щ�����Ƿǣ�����������˼��\n"NOR,me);
    message_vision("\n\n�������ֵ�ͷ��˼���ã�������\n\n\n\n"NOR,me);
	call_out("longgong_done4",5,me);
}

void longgong_done4(object me)
{
    command ("sigh");
    message_vision("�������쳤̾����" + RANK_D->query_respect(me) + "���ľ��������ҳ��������Ժ����в�ǲ������Ī�Ҳ��ӣ�\n"NOR,me);
}

void longgong_done1()
{
	object me;
	me=this_player();
    command ("sigh");
    message_vision(HIB"\n�����Ȼ���µ�����Ȼ���������ϵ�Ϊ��һʱ֮����Υ����۽�ּ
	Ҳ��������³�����������������\n\n\n"NOR,me);
}


void dropthing(string thing)
{
  command("drop "+thing);
  return;
}


int begin_yuanshoucheng()
{
	   object me,ob;
    me=this_player();
	ob=this_object();
   if (!me->query("fangcun/panlong_visite"))
	return 0;
		if (me->query_temp("fangcun/panlong_longgong_longzhu")!="done")
			{
		     command ("say �Ҷ��������ƹ��ĺ�ˮ��,��ʲô���²����˵ģ�\n");
			 return 1;
	    }

		if ((me->query("fangcun/panlong_longgong")=="done")||(me->query_temp("fangcun/panlong_longgong_yuanshoucheng")=="done"))
	    {
		     command ("say �����������ˣ��������������Σ�\n");
			 return 1;
	    }
	message_vision("\n\nһ�ᵽ�����£�����������ֻ�޵�ҧ���гݣ���������ŭ�ţ�\n\n"NOR,me);
    command("say "+RANK_D->query_respect(me)+"������֪ѽ��ǰ�վ���ˮ��������������������һ���������ݺ�������ʱ��
	�̣���ة��κ������۽�ּһ��ն֮���˳𲻱�����ˮ���к���Ŀ�ټ���·�ɼң�\n\n");
	command("say ����Ϊ���·��Ҫ���˱�ǰ���ض������ֻ꣬�־��˴��ư���������"+RANK_D->query_respect(me)+"
	��������书ֻҪ�������������������Ҵ�����������Ȼ��"+RANK_D->query_respect(me)+"��Ը����̨����\n");
    me->set_temp("fangcun/panlong_longgong_yuanshoucheng","begin");
return 1;
}

void die()
{
	object me,who,longjin;
    string whoid;
    me=this_object();
    if(me->query_temp("longjin_kill"))
	{
		  whoid=me->query_temp("longjin_kill");
    	  if (!present(whoid,environment()))
        	  return ::die();
	  	  who=present(whoid,environment());
          if((who->query("fangcun/panlong_hell_18")=="done")&&(who->query("fangcun/panlong_hell_longjin")=="begin")&&(environment()))
		{
			  longjin=new("/d/sea/obj/longjin");
			  longjin->move(me);
			  ::die();
			  return; 
		}
	}
      ::die();
}
