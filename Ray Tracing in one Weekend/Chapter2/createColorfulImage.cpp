void createColorfulImage(const char* path){
    ofstream outFile(path);
    if(outFile.fail()){
        cout << "Create file writing stream failed" << endl;
    }
    outFile << "P3\n200 100\n255\n";
    int nx = 200 , ny = 100;
    for(int y = ny-1; y >= 0; --y){
        vec3 rgb;
        rgb[1] = int(255 * float(y) / float(ny));
        for(float x = 0; x < nx; ++x){
            rgb[0] = int(255 * float(x) / float(nx));
            rgb[2] = int(255 * 0.2);
            outFile << rgb << endl;
        }
    }
    outFile.close();
}
