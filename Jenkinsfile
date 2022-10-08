#!/usr/bin/env groovy
pipeline{
    agent {
        docker { 
            image 'jenkins:v1'
        }
    }
    // triggers{
    //     pollSCM('H H(0-7) * * *')
    // }
    environment{
        TARGET_ROOTFS="/opt/nvidia/jetson4.2.2-all"
        LD_LIBRARY_PATH="${TARGET_ROOTFS}/usr/lib:$ROOT_PATH/usr/local/cuda/lib64:${TARGET_ROOTFS}/usr/lib:${TARGET_ROOTFS}/usr/lib/aarch64-linux-gnu/tegra:${TARGET_ROOTFS}/usr/lib/aarch64-linux-gnu:/usr/aarch64-linux-gnu/lib"
        PKG_CONFIG_PATH="${TARGET_ROOTFS}/usr/lib/aarch64-linux-gnu/pkgconfig"
        CROSS_COMPILE="aarch64-linux-gnu-"
    }
    parameters{
        choice(name:'choiceTage',choices:['NONE','lastTag'],description:'If you want build with gerrit url choise NONE.')
        string(name:'gerritUril',defaultValue:'',description:'paste the Cherry Pick cmd.')
    }
    stages{
        stage('checkout'){
            steps{
                sh """
                cd
                eval `ssh-agent -s`
                ssh-add
                """
                //git([branch: 'master', url:'ssh://developer.miivii.com:29418/miivii-sw-linux/bsp/miivii-gmsl-camera'])
            }
        }
        stage('prebuild'){
            steps{
                script{
                    env.DECRIBE_INFO = sh(returnStdout: true, script: "git describe --tags").trim()+"-0"
                    env.CURRENT_PLATFORM="${env.DECRIBE_INFO}".split("-v")[0]
                    env.TAG_VERSION="${env.DECRIBE_INFO}".split("-v")[1].split('-')[0]
                    // env.MAJORVER = "${env.TAG_VERSION}".split('\\.')[0]
                    // env.MINORVER = "${env.TAG_VERSION}".split('\\.')[1]
                    // env.PATCHVER = "${env.DECRIBE_INFO}".split("-v")[1].SplitString('-')[1]
                    env.DELAY_COMMIT_TAG="${env.CURRENT_PLATFORM}-v${env.TAG_VERSION}"
                    if (params.choiceTage == "NONE"){
                        sh """
                            (eval ${gerritUril})
                        """
                    } else {
                        sh """
                            git checkout -b ${DELAY_COMMIT_TAG} ${DELAY_COMMIT_TAG}
                        """
                    }
                    env.DEPLOY_BUILD_DATE = sh(returnStdout: true, script: "date -u +'%Y-%m-%dT%H:%M:%SZ'").trim()
                    env.DEPLOY_COMMIT_INFO = sh(returnStdout: true, script: "git log -1").trim()
                    env.DEPLOY_COMMIT_AUTH = sh(returnStdout: true, script: "git log -1 --pretty=format:'%an'").trim()
                    env.DEPLOY_COMMIT_EMAIL = sh(returnStdout: true, script: "git log -1 --pretty=format:'%ae'").trim()
                    env.JENKINS_URL=sh(returnStdout: true, script: "echo ${env.BUILD_URL} | sed \"s/miivii.jenkins/192.168.31.110/g\"").trim()
                }
                sh """
                    git submodule init
                    git submodule update
                """
            }
        }
        stage("build"){
            steps{
                sh """
	                make package -j8 CPPFLAGS+=\"-std=c++11 -fPIC --sysroot=${TARGET_ROOTFS} \
                        -I/usr/local/include/opencv \
                        -I/usr/include/opencv \
                        -I/usr/include \
                        -I/usr/include/drm \
                        -I${WORKSPACE}/common/include \
                        -I${WORKSPACE}/common/include/libjpeg-8b \
                        -I${WORKSPACE}/common/algorithm/cuda \
                        -I${WORKSPACE}/common/algorithm/trt \
                        -I/usr/local/cuda/include \
                        -I/usr/include/aarch64-linux-gnu \
                        -I/usr/include/libdrm \
                        -L${WORKSPACE}/source -I${WORKSPACE}/source\"
                """
            }
            post{
                success{
                    archiveArtifacts artifacts: '**/*.deb', fingerprint: true
                    gerritReview labels: [Verified: 1]
                }
                unstable { gerritReview labels: [Verified: 0], message: 'Build is unstable' }
                failure { gerritReview labels: [Verified: -1] }
            }
        }
    }
    post{
        always {
            deleteDir()
        }
        success {
            mail to: "wjyang@miivii.com,${env.DEPLOY_COMMIT_EMAIL}",
            subject: "[Jenkins] The project' ${JOB_NAME} ' verify succeed, please test it.",
            body: """
Hi,${env.DEPLOY_COMMIT_AUTH}
    Please go to ${env.JENKINS_URL} and test it.Build date is ${env.DEPLOY_BUILD_DATE}.

The last commit is:
${env.DEPLOY_COMMIT_INFO}
            """
        }
        failure{
            mail to: "wjyang@miivii.com,${env.DEPLOY_COMMIT_EMAIL}",
            subject: "[Jenkins] The project' ${JOB_NAME} ' verify failed :( ,please check you commit.",
            body: """
Hi,${env.DEPLOY_COMMIT_AUTH}
    Please go to ${env.JENKINS_URL} and check the commit.Build date is ${env.DEPLOY_BUILD_DATE}.

The last commit is:
${env.DEPLOY_COMMIT_INFO}
            """
        }
    }
}
