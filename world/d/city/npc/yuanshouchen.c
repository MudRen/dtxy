inherit NPC;
inherit F_MASTER;
string suanming(object me);
string suan_fuyuan(object me);
string suan_rsg(object me);
string ask_mieyao();
string ask_cancel();

string ask_sihou();
 int longwang();
void create()
{
        set_name("Ԭ�س�", ({"yuan shoucheng","yuan"}));
        set("title","��������");
        set("gender", "����" );
        set("age", 55);
        set("class","taoist");
        set("long", "��֪��������������飮��������û�в���ʶ���ġ�\n");
        set("combat_exp", 800000000);
        set("daoxing", 80000000);

        set("attitude", "peaceful");
        set_skill("unarmed", 10);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("literate", 50);
        set_skill("spells", 50);
        set_skill("mysticism", 50);
set_skill("whip", 150);
        set_skill("wuwei-fuchen", 180);
        set_skill("binfen-steps", 50);
        
        set("per", 15);
   set("max_kee", 350000);
        set("max_gin", 300000);
        set("max_sen", 300000);
        set("max_mana", 200000);
        set("mana", 200000);
        set("mana_factor", 1000);
        create_family("����ɢ��", 1, " ��");
        setup();
        carry_object("/d/obj/cloth/choupao")->wear();
}

void init()
{
        object ob;

        ::init();
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
            "suanming" : (: suanming :),
"�����ĺ�" : (: ask_sihou :),
 "��������" : (: longwang :),
 "����": (: ask_mieyao :),
           "cancel": (: ask_cancel :),
         ]) );

        set("chat_msg", ({
            "Ԭ�سϻ��˻����ϵĹ𻨾ƴ�Ц����������û���ë�������Ǻõ������\n",       
                "Ԭ�س��������´������㼸�ۡ�\n",
                "Ԭ�س�������ü��һ��������ֹ�����ӡ�\n",
                "Ԭ�س��������������������һ�£����������������\n�͹����û�����Ķ����þ���\n",
        }) );
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
string ask_mieyao()
{
    object who=this_player();

    if((string)who->query("family/family_name")=="����ɢ��") {
      command("smile "+who->query("id"));
      return "/d/obj/mieyao"->query_yao(who);
    }
    return ("��������,�ι�����?\n");
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
                call_out("destroy", 2, ob);
                return 1;
        }
        else if( (string)ob->query("name")=="��ɫ����" 
                 && (string)ob->query("id")=="fish" )
        {
                message_vision("Ԭ�س�����ѻ��ض�$N������л"+RANK_D->query_respect(me)+"����������Ҫ�������ʲô�����������ʣ�\n", me);
                me->set_temp("suanming/paid", 1);
                call_out("destroy", 2, ob);
                return 1;
        }
        else
        {
            command("say ���ҵ����ҵ���������̫�����ˡ�");
            return 1;
        }
}


// add by mind
void attempt_apprentice(object me)
{
        
if((string)me->query("family/family_name")=="����ɢ��")
    {
      command("recruit " + me->query("id"));
        me->set("class", "sanxian");
        me->set("title","����ɢ�� ��ʿ");
    }
        call_out("do_recruit", 2, me);
        command("say ��ֻ�Ἰ������è�Ĺ��򡣡���\n",);
                             
        
}

void do_recruit(object ob)
{
     /*     if((int) ob->query_temp("wait_time") < 360)
        
        {
          command("say ���²��������ӵܰ�������\n");
        return;
        }
        if((int)ob->query("water") > 0 || (int)ob->query("food") > 0)
        {
          command("say ���²��������ӵܰ�������\n");
        return;
        }*/
          if(ob->query("daoxing") > 50000 || ob->query("combat_exp") > 50000)
        {
          command("say ���²��������ӵܰ�������\n");
        return;
        }
        else {

                command("sigh");
                command("say ����ĳϣ����¾ʹ�������������պ�������й�����");
                command("recruit " + ob->query("id") );
        }
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "sanxian");
                ob->set("title", "����ɢ�� ��ʿ");
}
string ask_sihou()
{
        object who,me,room;
        
        who = this_player();
        me = this_object();
if ( who->query("family/family_name") == "����ɢ��"){
        command("sigh " + who->query("id"));
        command("say " + "���֮�乲��ʮ��֮�֣����ɣ��졢�ء����ˡ���
        ��棺�����ۡ�ë���������������ĺ�ȴ�����ʮ��֮�С�����ʯ���
        ���Ǵ����칬�������ߣ�����⨺��ֳ�û�ڻ���ɽ������ͨ��Գ���������¡�
        ��ǧɽ�����ݾ̣�Ǭ��ĦŪ�������������������¡��Ƴ��롢���������ĳ�
        �������Ͷ̥���䣬�����ʥ����������ͿĨ�˺��������֣�����λշת��
        �ֻ�֮�⣬�����������˹���Ҳ��\n");
        command("say " + "��ͨ��Գ�Ｘ����ǰ������ټ�����֮ʱһ��������ʦ��
        �����������ֲ����ף���������һ�̣�ȴҲ������\n");
        if(!( room = find_object("/d/sanxian/caodi")) )
            room = load_object("/d/sanxian/caodi");
        if(objectp(room))
            who->move(room);
        return "\nԬ�س�����һ����ĺ��ģ��͵����һ����������\n\n";
}
}
int longwang()
{
  object me;
   me=this_player();
 if (me->query_temp("fangcun/panlong_longgong_yuanshoucheng")!="begin")
 return 0;
 if( !me->query_temp("longwang_yuan") && !me->query_temp("longwang_xian") )
 {
	command("sigh");
	command("say ��λ" + RANK_D->query_respect(me) + "ֻ֪��һ��֪�����С���ڳ���������Ϊ����ǰ����Ϊһ���������
    ����ʱ�δ��������ǰ��°��У�˭֪������������������һ��������һ��ʿ����������;
    �£�С����ʵ��֪��������Ϊ������Υ�����ּ�⣬����ʱ�������˳ߴ磮������С��;
    �鷳��˵�����Բ�׼Ҫ��С���������ǣ�����С��ֻ��ʶ������������Ŀ����ָ������;
    ������ȥ�󵱳����̫��������ة��κ�����ָ����飬̫�ڻʵ�Ϊ�������������ڵ���;
    ��ĩ���֮��������κ������Ǳ������һ�֣�˭֪��ʱ����һ����κ���о�δ�գ���;
    ����˯��������ǵ����̨ն������������" + RANK_D->query_respect(me) + "�������ſ�ȥ�ʹ����մ�ּ������;
      ��������ɽ�������������һ��\n");
   me->set_temp("longwang_yuan",1);
   me->set_temp("help_yuan","yes");
 }
 else if( me->query_temp("longwang_yuan") )
 {
 	command("say ��λ" + RANK_D->query_respect(me) + "�����������������");	
 }
 else
 {
 	command("say ��λ" + RANK_D->query_respect(me) + "�뽫��ּ������������˵�����Ծ�ʦ��˶��ǳ����Σ���Ϊ����ұۣ�");	
 }
return 1;
}
void destroy(object ob)
{
        destruct(ob);
        return;
   }