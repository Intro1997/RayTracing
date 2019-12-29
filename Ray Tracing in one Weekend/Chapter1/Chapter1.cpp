void createColorfulImage(const char* path){
    ofstream outFile(path);
    if(outFile.fail()){
        cout << "Create file writing stream failed" << endl;
    }
    outFile << "P3\n200 100\n255\n";
    int nx = 200 , ny = 100;
    for(int y = ny-1; y >= 0; --y){
        vec3 rgb;
       int G = 255 * float(y) / float(ny);
        for(float x = 0; x < nx; ++x){
           int R = 255 * float(x) / float(nx);
           int B = 255 * 0.2;
           outFile << R << " " << G << " " << B << endl;
        }
    }
    outFile.close();
}
