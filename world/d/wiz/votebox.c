//ͶƱ����
//������������ͶƱ��Ϣ������ѡ�����Ϣ��,ͳ��ͶƱ���������ͶƱ�ʸ�
//�Զ�����ͶƱ���ϡ�����(�������ᴢ����/data/vote/ Ŀ¼����)
//��ʦ����ʹ������ָ��������ͶƱ��,set_exp��set_box
//set_exp ���Ʋ���exp��dummyͶƱ,ָ���ʽΪset_exp number

//set_box ��Ϊ����,��һ��,ϵͳҪ��������ͶƱ�Ĵ���,���������ŵ�ͶƱ��������,
//��ôϵͳ���Զ������������,ʹ�ô˴��ŵ�ͶƱ���������!
//���������������ŵĵ���,��ô�����ڶ���,�������е�ѡ����ܸ���,
//������,����������ͶƱ����,�������е�ѡ��,�Ƽ���ʽΪ:
//
//    ������Ϊ........��ͶƱ
//    1. ʲôʲô...........
//    2. ʲôʲô............
//    3. ʲôʲô............
//    4. ʲôʲô...........
//    ............

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;
int exp=0;
string vote_string="";// ͶƱ��������
int choose_number;// ѡ����Ŀ
int vote_number; //�Ѿ�Ͷ����Ʊ��
string title="temp";// ����ͶƱ�����,���ݴ˴��Ž�ͶƱ���ϴ浵,�����Ժ��ѯ

int get_vote_title(string arg,object me);
int get_vote_string(string arg,object me);
int get_choose_number(string arg,object me);

void init()
{
       add_action("do_vote","choose");
       add_action("do_set_box","set_box");
//     add_action("do_check_result","check_result");
       add_action("do_look","look");
       add_action("do_set_exp","set_exp");
}

int do_set_exp(string arg)
{
       int i;
       if (!arg || sscanf(arg,"%d",i)!=1) return notify_fail("��ȷʹ�ø�ʽӦ����set_exp number!\n");
       exp=i;
       this_object()->set("vote_exp",exp);
       this_object()->save();
       write("�ܲμӱ���ͶƱ���������Ҫ����ѧ�͵��е��ܺ��޸�Ϊ--���볬��"+HIR+exp+NOR+".\n");
       return 1;
}

void create()
{
        set_name( HIW"��������"+HIR"ͶƱ��"NOR, ({ "vote box"}) );
        set_weight(9999999);
        set("unit", "��");
        set("no_clean_up",1);
        set("long",HIM"Ϊ�˴������θ��õķ�չ����Ͷ���������һƱ��лл��"NOR);
        setup();
}

int clean_up()
{
    return 0;
}

string query_save_file()
{
        return "/data/vote/vote"+title+".o";
}


int do_set_box()
{
        object me=this_player();
        if (!wizardp(me))
        {
                tell_object(me,"�Բ���ֻ����ʦ�ſ���ʹ�ô����\n");
                return 1;
        }
        tell_object(me,"�����úñ���ͶƱ�ı���,(����˱����ͶƱ��������,��ֱ������votebox)\n");
        input_to( (:get_vote_title:),me);
        return 1;
}
int get_vote_title(string arg,object me)
{
        if (arg=="")
        {
           tell_object(me,"�õ�,ȡ���˴β���!\n");
           return 1;
        }
        title=arg;
        if (this_object()->restore())
        {
                tell_object(me,"����Ϊ"+HIR+title+NOR"��ͶƱ�������ɹ�����!\n");
                return 1;
        }
        vote_string="";
        this_object()->set("vote_string","");
        tell_object(me,"�����뱾��ͶƱ��ѡ����Ŀ:(������ĸ�ͶƱ��,������'4')\n");
        input_to( (:get_choose_number:) ,me);

        return 1;
}

int get_choose_number(string arg,object me)
{
        int i;
        if (arg=="")
        {
                write("��������ȷ������!\n");
                return 1;
        }
        if (sscanf(arg,"%d",i)!=1)
        {
                write("��������ȷ������!\n");
                return 1;
        }
        choose_number=i;
        tell_object(me,"�����úñ���ͶƱ������:(ֻ����س�ȡ����������,����'.'��ʾ��Ϣ������ϡ�)\n");
        this_object()->set("vote_title",title);
        this_object()->set("choose_number",choose_number);
        input_to ( (:get_vote_string:) ,me);
        return 1;
}

int get_vote_string(string arg,object me)
{
        if (arg=="") return notify_fail(":(!����ͶƱ��������ȡ��!\n");

        if (arg=="." && vote_string!="")
         {
           this_object()->set("vote_string",vote_string);
           if (this_object()->save())
              tell_object(me,"ok!����ͶƱ������ϣ�ͬʱ�Ѿ�������/data/vote/vote"+HIR+title+NOR".o\n");
           else
              write("���,ͶƱ�����޷��浵,�����в��ҳ���ԭ��.\n");
           return 1;
         }
        vote_string+=arg+"\n";
        input_to( (:get_vote_string:) ,me);
        return 1;
}
int do_look(string arg)
{
        int i;
        object ob=this_object();
        choose_number=ob->query("choose_number");
        if (!arg || arg !="vote box") return 0;
        write(HIW"��������"HIR"ͶƱ��"HIW",(����choose 1|2|3..��ͶƱ,лл��֧�ִ������εķ�չ!)\n"NOR);
        write(HIG"=========================================================================\n"NOR);
        if (!ob->query("vote_string") || !ob->query("choose_number"))
        {
                write(HIR"����������ʱû��ͶƱ�!\n"NOR);
                return 1;
        }
        write(HIY"����ͶƱ����\n"NOR);
        write(HIW+ob->query("vote_string")+NOR+"\n");
        write(HIY+"ͶƱ����"+NOR+"\n");
        write(HIW+"���к���ѧ���ܺͳ���"+HIR+ob->query("vote_exp")+HIW+"���������!\n\n"NOR);
        write(HIY+"ĿǰͶƱ���\n"NOR);
        write(HIW+"Ŀǰ����"+HIR+ob->query("vote_number")+HIW"λ���Ͷ��Ʊ,����:\n"+NOR);
        for (i=1;i<=choose_number;i++)
          write(HIW+"ѡ"+HIR+i+HIW"�������"+HIR+ob->query(""+i+"/number")+HIW+"λ\n"+NOR);
        return 1;
}
int do_vote(string arg)
{
        int i;
        object ob=this_object();
        object me=this_player();
        string *arr;
        choose_number=ob->query("choose_number");
        if (!ob->query("vote_string") || !ob->query("choose_number"))
        {
                write(HIR"����������ʱû��ͶƱ�!\n"NOR);
                return 1;
        }
        if (!arg || sscanf(arg,"%d",i)!=1)
        {
                write(HIW"��ȷ��ͶƱ��ʽ��:choose ��Ӧ��ѡ������ !\n"NOR);
                return 1;
        }
        if (i<1 || i>choose_number)
        {
                write(HIR"û�����ѡ��!\n"NOR);
                return 1;
        }

        if (arr=ob->query("vote_id") )
          {
            if (member_array(me->query("id"),arr)!=-1 )
              {
                write( HIW"���λ,���Ѿ�Ͷ��һƱ��!\n"NOR);
                return 1;
              }
          }
        if (me->query("daoxing")+me->query("combat_exp")<ob->query("vote_exp") )
          {
            write(HIM"�Բ���,��ľ���ֵ������,��ʱ�޷��μ�ͶƱ!\n"NOR);
            return 1;
          }
        ob->add("vote_number",1);
        ob->add(""+i+"/number",1);
        ob->add("vote_id",({me->query("id") }));
        ob->save();
        write_file("/data/vote/vote"+ob->query("vote_title")+".txt",me->query("id")+" vote "+i+"\n");
        write(HIM"����ͶƱ,��ѡ����ѡ��"+HIR+i+NOR+"\n");
        write(HIM"лл���Դ������ε�����֧��!GOOD LUCK!\n"NOR);
        return 1;
}
