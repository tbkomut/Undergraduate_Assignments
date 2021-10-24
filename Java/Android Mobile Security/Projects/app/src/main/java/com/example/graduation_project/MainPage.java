package com.example.graduation_project;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.content.pm.Signature;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Serializable;
import java.nio.Buffer;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutionException;
import java.util.jar.JarFile;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;


public class MainPage extends AppCompatActivity {

    private static ProgressDialog item;
    public static ArrayList<String> app_name_list = new ArrayList<String>();
    private ArrayList<String> apk_list = new ArrayList<String>();
    private ArrayList<String> package_list = new ArrayList<String>();
    private ArrayList<String[]> package_permissions = new ArrayList<String[]>();
    static final int progress_bar_type=0;
    private ArrayList<String> permission_message = new ArrayList<>();
    public static int endDocTag = 0x00100101;
    public static int startTag =  0x00100102;
    public static int endTag =    0x00100103;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        RelativeLayout currentLayout = (RelativeLayout) findViewById(R.id.back_color);
        currentLayout.setBackgroundResource(R.color.SkyBlue);
        Button button = (Button) findViewById(R.id.button2222);
        button.setBackgroundResource(R.color.ButtonColor);
        final Map<Map<String,Integer>,String>[] item = new Map[]{new HashMap<>()};
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            // Async tasks
            public void onClick(View v) {
                gettingAPKSProcess task = new gettingAPKSProcess();
                task.execute();
                try {
                    item[0] = task.get();
                    if (item[0].size()==0){
                        Intent intent = new Intent(MainPage.this, ResultPage.class);
                        startActivity(intent);
                    }
                    else {
                        Intent intent = new Intent(MainPage.this, ListsAppsFragment.class);
                        intent.putExtra("app_list", (Serializable) item[0]);
                        intent.putExtra("perm_list", (Serializable) permission_message);
                        startActivity(intent);
                    }
                } catch (ExecutionException e) {
                    e.printStackTrace();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    @Override
    protected Dialog onCreateDialog(int id) {
        switch (id){
            case progress_bar_type:
                item = new ProgressDialog(MainPage.this);
                item.setIndeterminate(true);
                item.setMessage("İşlemleriniz Sürüyor.");
                item.setTitle("Uygulamalar Taranıyor...");
                item.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
                item.setCancelable(false);
                item.show();
                return item;
            default:
                return null;
        }
    }

    public class gettingAPKSProcess extends AsyncTask<Object, Object, Map<Map<String,Integer>,String>>{

        protected void onPreExecute() {
            super.onPreExecute();
            showDialog(progress_bar_type);
        }

        @Override
        protected Map<Map<String,Integer>,String> doInBackground(Object... objects) {
            gettingAPK();
            // Şüpheli izinler listesi
            Map<Map<String,Integer>,String> app_info = mobileToDatabase();
            // checkAppSignature();
            return app_info;
        }


        @Override
        protected void onPostExecute(Map<Map<String, Integer>, String> mapStringMap) {
            super.onPostExecute(mapStringMap);
        }

    }

    private void gettingAPK(){
        PackageManager pm = getPackageManager();
        Intent main = new Intent(Intent.ACTION_MAIN, null);
        main.addCategory(Intent.CATEGORY_LAUNCHER);
        List<ResolveInfo> packages = pm.queryIntentActivities(main, 0);
        for(ResolveInfo resolve_info : packages) {
            String apk_name= resolve_info.activityInfo.applicationInfo.publicSourceDir;
            String[] temp= apk_name.split("/");
            if(temp[1].equals("data") && temp[2].equals("app")) {
                String package_name = resolve_info.activityInfo.packageName;
                String app_name = null;
                try {
                    PackageInfo info = getPackageManager().getPackageInfo(package_name, PackageManager.GET_PERMISSIONS);
                    String[] permissions = info.requestedPermissions;
                    package_permissions.add(permissions);
                    app_name = (String) pm.getApplicationLabel(pm.getApplicationInfo(package_name, PackageManager.GET_META_DATA));
                } catch (PackageManager.NameNotFoundException e) {
                    e.printStackTrace();
                }
                System.out.println(app_name);
                package_list.add(package_name);
                app_name_list.add(app_name);
                apk_list.add(apk_name);
            }
        }
    }

    public  Map<Map<String,Integer>,String> mobileToDatabase() {
        int i=0;
        Map<Map<String,Integer>,String> app_info= new HashMap<>();
        String packet_name="";
        for(String str:app_name_list) {
            System.out.println(str);
            Map<String,Integer> temp= new HashMap<>();
            String apk_file_name = apk_list.get(i);
            packet_name = package_list.get(i);
            // Uygulamanın gerektirmiş olduğu izinler elde edilir.
            String[] permissions = package_permissions.get(i);
            // Manifest dosyasında tanımlanmış olan izinler elde edilir.
            ArrayList<String> manifestFilePermission = getManifestFile(apk_file_name);
            ArrayList<String> suspect_permission  = new ArrayList<>();
            String perm_temp="\n\n>> UYGULAMA ANALİZİ\n\n";
            if (permissions != null) {
                for(String permission:permissions){
                   if(manifestFilePermission.contains(permission))
                       System.out.println(permission + " doğrulandı!");
                   // Manifest dosyasında belirtilmiyor, fakat kullanılan izinler.
                   else {
                       suspect_permission.add(permission);
                       perm_temp = perm_temp +  " - " + permission + "\n" + "\n";
                       System.out.println(permission + " doğrulanamadı!");
                   }
                }
                if(!perm_temp.equals("\n\n>> UYGULAMA ANALİZİ\n\n"))
                    permission_message.add(perm_temp);
            }
            else{
                // Manifest dosyasında belirtiliyor, fakat kullanılmayan izinler...
                for(String permission:manifestFilePermission) {
                    suspect_permission.add(permission);
                    perm_temp = perm_temp + " - " + permission + "\n" + "\n";
                    System.out.println(permission + " ikaz iznidir.");
                }
                if(!perm_temp.equals("\n\n>> UYGULAMA ANALİZİ\n\n"))
                    permission_message.add(perm_temp);
            }
            ThresholdValue calculating_suspecios_value= new ThresholdValue();
            int th_val= calculating_suspecios_value.malwarePermissionCheck(suspect_permission,apk_file_name);
            System.out.println("Şüphe Değeri " + th_val);
            if(th_val>0) {
                temp.put(str, th_val);
                app_info.put(temp, packet_name);
            }
            i++;
        }
        return app_info;
    }


    private ArrayList<String> getManifestFile(String apkPath){
        ArrayList<String> local_permission=null;
        try {
            JarFile jf = new JarFile(apkPath);
            InputStream is = jf.getInputStream(jf.getEntry("AndroidManifest.xml"));
            byte[] xml = new byte[is.available()];
            int br = is.read(xml);
            local_permission= new ArrayList<>();
            gettingFromXML(xml,local_permission);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return local_permission;
    }

    public void gettingFromXML(byte[] xml,ArrayList<String> local_permission) {
        int numbStrings = LEW(xml, 4*4);
        int sitOff = 0x24;
        int stOff = sitOff + numbStrings*4;

        int xmlTagOff = LEW(xml, 3*4);
        for (int ii=xmlTagOff; ii<xml.length-4; ii+=4) {
            if (LEW(xml, ii) == startTag) {
                xmlTagOff = ii;  break;
            }
        }
        int off = xmlTagOff;
        int indent = 0;
        int startTagLineNo = -2;
        while (off < xml.length) {
            int tag0 = LEW(xml, off);
            int lineNo = LEW(xml, off+2*4);
            int nameNsSi = LEW(xml, off+4*4);
            int nameSi = LEW(xml, off+5*4);

            if (tag0 == startTag) {
                int tag6 = LEW(xml, off+6*4);
                int numbAttrs = LEW(xml, off+7*4);
                off += 9*4;
                String name = compXmlString(xml, sitOff, stOff, nameSi);
                startTagLineNo = lineNo;
                StringBuffer sb = new StringBuffer();
                for (int ii=0; ii<numbAttrs; ii++) {
                    int attrNameNsSi = LEW(xml, off);
                    int attrNameSi = LEW(xml, off+1*4);
                    int attrValueSi = LEW(xml, off+2*4);
                    int attrFlags = LEW(xml, off+3*4);
                    int attrResId = LEW(xml, off+4*4);
                    off += 5*4;
                    String attrName = compXmlString(xml, sitOff, stOff, attrNameSi);
                    String attrValue = attrValueSi!=-1
                            ? compXmlString(xml, sitOff, stOff, attrValueSi)
                            : "resourceID 0x"+Integer.toHexString(attrResId);
                    sb.append(" "+attrName+"=\""+attrValue+"\"");
                }
                if(name.equals("uses-permission")){
                    String permission_tag = sb.toString();
                    String[] tokens = permission_tag.split("\"");
                    local_permission.add(tokens[1]);
                }
                indent++;

            } else if (tag0 == endTag) {
                indent--;
                off += 6*4;
                String name = compXmlString(xml, sitOff, stOff, nameSi);
            } else if (tag0 == endDocTag) {
                break;

            } else {
                break;
            }
        }
    }

    public String compXmlString(byte[] xml, int sitOff, int stOff, int strInd) {
        if (strInd < 0) return null;
        int strOff = stOff + LEW(xml, sitOff+strInd*4);
        return compXmlStringAt(xml, strOff);
    }


    public static String spaces = "                                             ";
    public void prtIndent(int indent, String str) {
        System.out.println(spaces.substring(0, Math.min(indent*2, spaces.length()))+str);
    }

    public String compXmlStringAt(byte[] arr, int strOff) {
        int strLen = arr[strOff+1]<<8&0xff00 | arr[strOff]&0xff;
        byte[] chars = new byte[strLen];
        for (int ii=0; ii<strLen; ii++)
            chars[ii] = arr[strOff+2+ii*2];
        return new String(chars);
    }

    public int LEW(byte[] arr, int off) {
        return arr[off+3]<<24&0xff000000 | arr[off+2]<<16&0xff0000
                | arr[off+1]<<8&0xff00 | arr[off]&0xFF;
    }

    public void checkAppSignature() {
        final PackageManager pm = getPackageManager();
        Intent main = new Intent(Intent.ACTION_MAIN, null);
        main.addCategory(Intent.CATEGORY_LAUNCHER);
        List<ResolveInfo> packages = pm.queryIntentActivities(main, 0);
        for(ResolveInfo resolve_info : packages) {
            String apk_name = resolve_info.activityInfo.applicationInfo.publicSourceDir;
            String package_name = resolve_info.activityInfo.packageName;
            String app_name = null;
            String currentSignature = null;
            try {
                // RUN TIME CHECK USING ANDROID API
                PackageInfo packageInf = pm.getPackageInfo(package_name, PackageManager.GET_SIGNATURES);
                for (Signature signature : packageInf.signatures) {
                    byte[] signatureBytes = signature.toByteArray();
                    MessageDigest md = MessageDigest.getInstance("SHA");
                    md.update(signature.toByteArray());
                    currentSignature = Base64.encodeToString(md.digest(), Base64.DEFAULT);
                }


                // FROM APK FILE
                Signature releaseSig = pm.getPackageArchiveInfo(apk_name, PackageManager.GET_SIGNATURES).signatures[0];
                if (packageInf.signatures[0].hashCode() == releaseSig.hashCode())
                    System.out.println("İmza Doğrulama Başarılı");
            } catch (PackageManager.NameNotFoundException e) {
                e.printStackTrace();
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }
        }
    }

    private void printing_list(){
        int i=0;
        for(String str:app_name_list){
            System.out.println(apk_list.get(i));
            i++;
        }
    }

    protected ArrayList<String> getterApps(){
        return app_name_list;
    }

    public void QuitApp(View view) {
        Intent intent = new Intent(getApplicationContext(), EntryPage.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.putExtra("EXIT", true);
        startActivity(intent);
    }

}
