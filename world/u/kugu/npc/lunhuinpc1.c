//Changed by Start DHXY

#include <ansi.h>
inherit NPC;
string ask_for_leave();

void create()
{
        set_name(HIW"ת���ֻ�����"NOR, ({"lunhui pusa","pusa"}));
        set("gender", "Ů��" );
        set("age", 25);
        set("title",HIY"����������翣��ա��ޡ���"NOR);
        set("long", HIG"\n\n������������ƹ�ת���ֻصĴ��ǡ���������\n\n"NOR);
        set("combat_exp", 10);
        set("daoxing", 10);

        set("attitude", "peaceful");
        set("per", 40);
        set("max_kee", 20000);
        set("max_gin", 20000);
        set("max_sen", 20000);
        set("inquiry", ([
                "�ֻ�ת��" : (: ask_for_leave :),
                "Ͷ̥" : (: ask_for_leave :),
                ]) );
        setup();
        carry_object("/d/ourhome/obj/pink_cloth")->wear();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void init()
{
        add_action("do_agree", "agree");
}

string ask_for_leave()
{
        object me=this_player();
        int zslev = me->query("lunhui_zhuanshi");
        int i,level;
        mapping skill;
        string *skillnames;

	if ( (int)me->query("lunhui_zhuanshi") >= 5 )
        	return HIM"ֻ��ת��5�Σ�\n"NOR;
        if ( (int)me->query("combat_exp") < 11000000 + zslev * 10000000 )
        	return HIW"�����ѧ����������100W��ѧ��һǧ����к�ÿһǧ����ѧ��һ������п���ת��һ�Σ�\n"NOR;
        if ( (int)me->query("daoxing") < 11000000 + zslev * 10000000 )
                return HIM"��ĵ��л���������100W��ѧ��һǧ����к�ÿһǧ����ѧ��һ������п���ת��һ�Σ�\n"NOR;
        if ( (int)me->query("obstacle/number") < 26)
                return HIM"����ȥȡ����������ת���ɣ�\n"NOR;
        if ( (int)me->query("dntg/number") < 10)
                return HIM"�㻹ûȥ��ͥ�����칬��ô����ת����\n"NOR;
        if ( (int)me->query("12gong/number") < 12)
                return HIM"�㻹û�����ƽ�12����ô����ת����\n"NOR;
        /*if ( (int)me->query("mingjie/number") < 15)
                return HIM"�㻹û����ڤ����ô����ת����\n"NOR;
        if ( (int)me->query("9sky/number") < 9)
                return HIM"�㻹û������������ô����ת����\n"NOR;
        */
	if ( (int)me->query_skill("literate", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("parry", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("force", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("spells", 1) >= 400 + (zslev*100)
		&& (int)me->query_skill("dodge", 1) >= 400+ (zslev*100) )
	{
                me->set_temp("c_lunhui", 2);
                return HIR"���˼�ǹ����ֻ�ת�����ɶ�Ϸ��������Ѿõ��书����з��涼Ҫ�������׺�ɣ��������ң����Ը���������һ�е�һ�У��ƺ쳾�������ң���ʦ���ţ���Ը���(agree)��"NOR;
        }
        return HIG"����书�����򻹲�������Ҫ�������ܴﵽ400��ת����������100�ĵȼ��ſ���ת����\n"NOR;
}

int do_agree(string arg)
{
        int i,j,level;
        mapping skill;
        object who=this_player();
        object env, link_ob, obj;
        int zslev = who->query("lunhui_zhuanshi");
        string *skillnames,*xing,*ddel,*fa,family;
        seteuid(getuid());
        /*xing=({
               "str", "cor", "int","spi",
               "cps", "per", "con","kar",
               });
        ddel=({
                "gifts",       "dntg",
                "obstacle",     "shengri",
                "12gong",       "mingjie",                               
                "quiz_num",     "secmieyao_mudage",
                "secmieyao",    "secmieyao_killedtime",
                "MKS",          "bellicosity",
                "9sky"
                });*/
	ddel=({
                "obstacle",       "dntg",
                "12gong",       "bellicosity",
		"gift",
         });
        family=who->query("family/family_name");
        
        if(!who->query_temp("c_lunhui") )
	{
                 command("say �������������");
                 return 1;
        }
        if(who->query_temp("c_lunhui") > 1 )
        {
                message_vision("$N"HIR"˵�������쳾�����������ֻ�ת��������һ������������\n\n", who);
                command("say "HIW"��Ȼ��ˣ������ھ������������������쳾֮��Բ�㳬��֮�⣡�����"+chinese_number(zslev+1)+"��������ë��\n\n");
               
         	who->add("combat_exp", -(10000000 + zslev * 10000000) );
         	who->add("daoxing", -(10000000 + zslev * 10000000) );
        	who->set("maximum_mana", 0);
         	who->set("max_mana", 0);
         	who->set("max_force", 0);
         	who->set("maximum_force", 0);
         	who->set("mud_age", 100000);
         	who->set("title", HIW"ת���ֻ�"+ HIY"����һ��������"NOR);
          

          	//��������趨ת��֮���int+2
		who->set("int", who->query("int") + 2);

         	//������������Ĳ����������ظ���һ�����Ǻܿ���ģ�����ȡ����״̬��
         	for(i=0;i<sizeof(ddel);i++)
         	{ 
                	who->delete(ddel[i]);
		}
         
         	// �������skills������Ҳ��lying�ϴ��ֵģ���
         	skill=who->query_skills();
         	skillnames=keys(skill);
         	for(i=0;i<sizeof(skillnames);i++)
         	{
            		who->set_skill(skillnames[i], 200);
          	}
 
                who->add("obstacle/rebirth",-(zslev+1) );
                who->add("lunhui_zhuanshi", 1);
                who->add("lunhui/lunhui",1);
                //who->delete("learned_points");
                who->delete("death");
                who->delete_temp("betray");
		obj = present("huangjin shengyi", who);
		if(objectp(obj))
			destruct(obj);
                who->set("startroom","/d/city/kezhan");

                command("say �����ڼ���������\n");
                command("chat "HIG"����һ���������㡣��������̥����ʪ��������������ɫ����ɫ�������������롣���������������롣���������缰����˵��\n\n");
                command("chat "HIR"��Ӧ��ס���ġ���Ӧ��ס�Ƿ��ġ���Ӧ������ס�ġ����Թʡ�������ס��Ϊ��ס�ʡ�\n\n");
                command("chat "HIC"�ֻ�ת���տյ�ȥ��������������һ�ȣ�"HIR""+who->query("name")+""HIC"�ƺ쳾֮�������׷���Ĺ��ҷ��ֻ�ת���ˡ�\n\n");

                who->move("/d/city/kezhan");
                env = environment(who);
                link_ob = who->query_temp("link_ob");
	        /*obj = LOGIN_D->make_body(link_ob);
	        if (!obj) return 0;
                who->save();
	        exec(link_ob, who);
	        destruct(who);
                obj->restore();
	        LOGIN_D->enter_world(link_ob, obj, 1);*/
                write(""BLINK""HIY"�㾭���˵�"HIR""+chinese_number(zslev+1)+""HIY"��ת���ֻء�\n\n"NOR);
                //obj->move(env,1);
	        //obj->write_prompt();         
            
                return 1;  //ת������Ϊֹ����ת����ص��ļ�damage.c��human.c��updated.c
	}    
} 

int accept_fight(object me)
{
        return 0;
}

int accept_kill(object me)
{
        return 1;
}
