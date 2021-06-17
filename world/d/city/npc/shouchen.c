// teller.c
//cglaem...12/16/96.
#include <ansi.h>

inherit NPC;

string suanming(object me);
string suan_fuyuan(object me);
string suan_rsg(object me);
int longwang();

void create()
{
        set_name("Ԭ�س�", ({"yuan shoucheng","yuan"}));
        set("title","��������");
        set("gender", "����" );
        set("age", 55);
        set("class","taoist");
        set("long", "��֪��������������飮��������û�в���ʶ���ġ�\n");
        set("combat_exp", 8000);
        set("daoxing", 80000);

        set("attitude", "peaceful");
        set_skill("unarmed", 10);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("literate", 50);
        set_skill("spells", 50);
        set("per", 15);
        set("max_kee", 350);
        set("max_gin", 300);
        set("max_sen", 300);
        set("max_mana", 200);
        set("mana", 200);
        set("mana_factor", 5);
        setup();
        carry_object("/d/obj/cloth/choupao")->wear();
}

void init()
{
    object me;
    me=this_player();
        ::init();
        add_action("do_answer", "answer");

  if(me->query_temp("longwang_xian")==1)
	{
	  call_out("ask_help",2);
	  return;
	}
		set("chat_chance", 10);
        set("inquiry", ([
                "name" : "С����Ԭ���سϣ������ٺ٣����ⳤ��һ������С�б�����\n",
                "here" : "��û������������ط��������µ�һ�������ڡ�\n", 
            "�˲ι�" : (: suan_rsg :),
            "rsg" : (: suan_rsg :),
            "��Ե" : (: suan_fuyuan :),
        "fuyuan" : (: suan_fuyuan :),
            "����" : (: suanming :),
            "����" : (: suanming :),
	    "��������" : (: longwang :),	    
		"suanming" : (: suanming :),
         ]) );

        set("chat_msg", ({
            "Ԭ�سϻ��˻����ϵĹ𻨾ƴ�Ц����������û���ë�������Ǻõ������\n",       
                "Ԭ�س��������´������㼸�ۡ�\n",
                "Ԭ�س�������ü��һ��������ֹ�����ӡ�\n",
                "Ԭ�س��������������������һ�£����������������\n�͹����û�����Ķ����þ���\n",
                (: random_move :)
        }) );
}


void ask_help()
{
	 object me;
    me=this_player();
    command("hi " + me->query("id"));
    command("say "+RANK_D->query_respect(me)+"���¿�֪��ƶ�����Է����ˣ�����ƶ�����붫�������������£�
    ��֪"+RANK_D->query_respect(me)+"��Ը����ң�����������Ը�⣯��Ը�⣩\n");
}

int do_answer(string arg)
{	
      object me,paper;
    me=this_player();

	  if(!me->query_temp("longwang_xian"))
		  return 0;
		if( !arg ) return notify_fail("����ش�ʲô��\n");
        message_vision("$N�����" + arg + "\n", me);
        if( arg== "Ը��" ) {
                command("bow");
				command("say "+RANK_D->query_respect(me)+"���������ĳ���ƶ��������л���ˣ���������һ����������
	  ����ն����������ڵ�������������ּ����������������㿴
	  �������Ƕ������������ǷǾ�����ã���ȻҲ���������ˣ�\n");
				paper=new("/d/sea/obj/jinzhi");
				paper->set("longgong_pass",1);
				paper->move(me);
        message_vision("\nԬ�سϽ���$Nһ��ɫ�����̽�ߵ�"+HIY"˿��"+NOR"��\n\n", me);
		me->delete_temp("longwang_xian");
		me->set_temp("help_yuan","yes");
        } else if( arg== "��Ը��" ) {
                command("say ��ϧ��ϧ��ƶ����ֻ���Լ�ȥһ�˶��������ˣ�\n");
				me->delete_temp("longwang_xian");
				me->set_temp("help_yuan","no");
        } else {
			   command("say ��˵ʲô��\n");
		}
        return 1;
}

string suan_fuyuan(object me)
{
       int my_level;

       string *levels = ({
         "ù�����죬ˡ����ֱ�ԣ�Ѫ��֮�ֲ�Զ�ӣ�\n",
         "ӡ�÷�����������������\n",
         "�˵��пɡ�\n",
         "������Ե��ǳѽ����\n",
         "���Ƕร����֮�ˡ�\n",
         "����������Ե����ϲ����ϲ��\n",
         "���Ǹ��綫�����ٱ���ɽѽ��\n",
          });

        me = this_player();

my_level=(me->query("gift_modify/kar")+me->query("kar")+me->query("donation")/1000000)/5-2;
        if(my_level>6 ) my_level=6;
        if( !me->query_temp("suanming/paid") )
        {
                if( me->query_temp("suanming/asked") ) 
                {
                        message_vision("Ԭ�سϱ����۾�������$N�ˡ�\n", me);
                        return "��������һ����ɫ���㣬��֪"
                          +RANK_D->query_respect(me)+"�ܷ������\n";
                }
                else
                {
                        me->set_temp("suanming/asked", 1);
                        message_vision("Ԭ�س��ϳ������ɿ��˼�����\n", me);
                        return "����������������й¶����\n";
                }
        }
        else
        {
                me->delete_temp("suanming");
                message_vision("Ԭ�س϶�$N�����������Ҷ����ˣ�˵����ָ���˼��㡣\n", me);
                if(my_level<0 )
                        return "��֣�"+RANK_D->query_respect(me)+
                            "����ʮ�ֹ��죬������Ϊ�������㲻����������\n";
                else
                   return RANK_D->query_respect(me)+levels[my_level];
        }
}

string suan_rsg(object me)
{
        me = this_player();

        if( !me->query_temp("suanming/paid") )
        {
                if( me->query_temp("suanming/asked") ) 
                {
                        message_vision("Ԭ�سϱ����۾�������$N�ˡ�\n", me);
                        return "��������һ����ɫ���㣬��֪"
                          +RANK_D->query_respect(me)+"�ܷ������\n";
                }
                else
                {
                        me->set_temp("suanming/asked", 1);
                        message_vision("Ԭ�س��ϳ������ɿ��˼�����\n", me);
                        return "����������������й¶����\n";
                }
        }
        else
        {
                me->delete_temp("suanming");
                if(me->query("rsg_eaten")<=0)
                    return RANK_D->query_respect(me)+
                        "��û�����˲ι�����ζ�˰ɣ�";
                else
                message_vision("Ԭ�س϶�$N�����������Ҷ����ˣ�˵����ָ���˼��㡣\n", me);
                   return "��˵"+RANK_D->query_respect(me)+"�Ѿ�����"+
                       chinese_number(me->query("rsg_eaten"))+"���˲ι������Ǹ�Ե��ǳѽ��\n";
        }
}


string suanming(object me)
{
        me = this_player();

        if( !me->query_temp("suanming/paid") )
        {
                if( me->query_temp("suanming/asked") ) 
                {
                        message_vision("Ԭ�سϱ����۾�������$N�ˡ�\n", me);
                        return "��������һ����ɫ���㣬��֪"
                          +RANK_D->query_respect(me)+"�ܷ������\n";
                }
                else
                {
                        me->set_temp("suanming/asked", 1);
                        message_vision("Ԭ�س��ϳ������ɿ��˼�����\n", me);
                        return "����������������й¶����\n";
                }
        }
        else
        {
                me->delete_temp("suanming");
                message_vision("Ԭ�س϶�$N�����������Ҷ����ˣ�˵����ָ���˼��㡣\n", me);
                if(me->query("life/live_forever"))
                        return "ʧ����ʧ����ԭ��"+
                            RANK_D->query_respect(me)+
                            "���������⣬���������У�����������������ˣ�\n";
                else if(me->query("age")<16)
                    return RANK_D->query_respect(me)+
                        "���᳤�����꣬ǰ;����������\n";
                else
                   return RANK_D->query_respect(me)+"��"+
                       chinese_number(me->query("life/life_time"))+"������١�\n";
        }
}

int accept_object(object me, object ob)
{
        object nowords;
        
        if(userp(ob)) return 0;

        if( (string)ob->query("name")=="�𻨾ƴ�" )
        {
                command("u&me " + me->query("id"));
                command("say ��λ" + RANK_D->query_respect(me) + "���Ǹ���ͶԵ��\n������Ҳ��һ��С��˼����Ц�ɡ�\n");
                carry_object("/d/obj/book/nowords");
                command("give nowords to " + me->query("id"));
                return 1;
        }
        else if( (string)ob->query("name")=="��ɫ����" 
                 && (string)ob->query("id")=="fish" )
        {
                message_vision("Ԭ�س�����ѻ��ض�$N������л"+RANK_D->query_respect(me)+"����������Ҫ�������ʲô�����������ʣ�\n", me);
                me->set_temp("suanming/paid", 1);
                return 1;
        }
        else
        {
            command("say ���ҵ����ҵ���������̫�����ˡ�");
            return 1;
        }
}

int longwang()
{
	  object me;
    me=this_player();
	  if (me->query_temp("fangcun/panlong_longgong_yuanshoucheng")!="begin")
	  return 0;
	command("sigh");
	command("say ��λ" + RANK_D->query_respect(me) + "ֻ֪��һ��֪�����С���ڳ���������Ϊ����ǰ����Ϊһ����������ԣ���
	    ����ʱ�δ��������ǰ��°��У�˭֪������������������һ��������һ��ʿ����������
	    �£�С����ʵ��֪��������Ϊ������Υ�����ּ�⣬����ʱ�������˳ߴ磮������С��
	    �鷳��˵�����Բ�׼Ҫ��С���������ǣ�����С��ֻ��ʶ������������Ŀ����ָ������
	    ������ȥ�󵱳����̫��������ة��κ�����ָ����飬̫�ڻʵ�Ϊ�������������ڵ���
	    ��ĩ���֮��������κ������Ǳ������һ�֣�˭֪��ʱ����һ����κ���о�δ�գ���
	    ����˯��������ǵ����̨ն������������" + RANK_D->query_respect(me) + "�������ſ�ȥ�ʹ����մ�ּ������
	    ��������ɽ�������������һ��\n");
    me->set_temp("longwang_yuan",1);
	return 1;
}
